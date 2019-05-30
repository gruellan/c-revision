#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN(ARR) (sizeof(ARR) / sizeof(*(ARR)))

/**
 * Possible symbols that can be rolled.
 */
const char *const symbols[] = {"bell", "orange", "cherry", "horseshoe"};

#define NUM_SYMBOLS ARRAY_LEN(symbols)

const uint8_t longest_symbol = 9;

struct roll_result {
  enum { ROLL_LOSE, ROLL_WIN, ROLL_JACKPOT } result;
  uint matching_symbols;
};

// NOTE: this [<idx>] = <expr>, syntax is a GNU C extension, supported by GCC
// and CLang: https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html
/**
 * Map of result values to the text to print.
 */
const char *const result_text[] = {[ROLL_LOSE] = "You lose",
                                   [ROLL_WIN] = "You win!",
                                   [ROLL_JACKPOT] = "Jackpot!!"};

static void sleep_ms(uint num_ms) {
  struct timespec ts;

  ts.tv_sec = num_ms / 1000;
  ts.tv_nsec = (num_ms % 1000) * 1000000;

  nanosleep(&ts, NULL);
}

/**
 * Random function that seeds the first time called
 *
 * @returns a random number in the range (min, max]
 */
static int get_random(int min, int max) {
  assert(min < max);

  static bool is_seeded = 0;

  if (!is_seeded) {
    srand(time(NULL));
    is_seeded = true;
  }

  return (rand() % (max - min)) + min;
}

/**
 * Roll the wheel once.
 */
static int roll_wheel(void) { return get_random(0, NUM_SYMBOLS); }

/**
 * Check the symbols that were rolled.
 *
 * If all match: jackpot.
 * If any match: win.
 * If none match: lose.
 */
static struct roll_result check_rolls(const int *const rolls,
                                      size_t num_rolls) {
  // since we ensure we select the strings from the array
  // we can compare them as pointers

  // start assuming a jackpot
  bool is_jackpot = true;

  uint matching_symbols = 0;

  for (size_t i = 0; i < num_rolls; i++) {
    // start j at i+1, we check all the rolls to the right of i
    for (size_t j = i + 1; j < num_rolls; j++) {
      if (rolls[i] == rolls[j]) {
        matching_symbols++;

        // once we know a symbol has a match, we can skip to the next one
        break;
      }

      // any non matching symbols means the jackpot wasn't hit
      is_jackpot = false;
    }
  }

  return (struct roll_result){
      .matching_symbols = matching_symbols,
      .result = is_jackpot ? ROLL_JACKPOT
                           : (matching_symbols ? ROLL_WIN : ROLL_LOSE)};
}

static void print_rolls(const int *const rolls, size_t num_rolls) {
  assert(num_rolls > 0);

  printf("%*s", longest_symbol, symbols[rolls[0]]);

  for (int i = 1; i < num_rolls; i++) {
    printf(" - %*s", longest_symbol, symbols[rolls[i]]);
  }
}

/**
 * Render the rolls made in a rotating fashion.
 */
static void render_rotating_rolls(int *const rolls, size_t num_rolls) {
  struct rotation_pos {
    int idx;
    int steps_left;
  };

  struct rotation_pos *positions =
      malloc(sizeof(struct rotation_pos) * num_rolls);

  int max_steps = 0;

  for (int i = 0; i < num_rolls; i++) {
    // random position this roll will start at
    int init_pos = roll_wheel();

    // how  many rotations we need to make to get to the destination symbol
    int num_steps_to_dest = (rolls[i] - init_pos + 1) % NUM_SYMBOLS;

    // cycle the roll some extra times.
    //
    // NOTE: we need to do at least 1 cyclehere, since num_steps_to_dest
    // will be negative half the time.
    int extra_cycles_to_do = get_random(1, 5);

    int num_steps = num_steps_to_dest + extra_cycles_to_do * NUM_SYMBOLS;

    if (num_steps > max_steps) {
      max_steps = num_steps;
    }

    positions[i] =
        (struct rotation_pos){.idx = init_pos, .steps_left = num_steps};
  }

  // print a single newline to put the animation on
  printf("\n");

  while (max_steps--) {
    for (int i = 0; i < num_rolls; i++) {

      // if this roll has finished it's animation
      if (!positions[i].steps_left) {
        continue;
      }

      rolls[i] = positions[i].idx;

      positions[i].idx = (positions[i].idx + 1) % NUM_SYMBOLS;
      positions[i].steps_left--;
    }

    // clear the line and return the cursor to the start of the line
    printf("\33[2K\r");

    print_rolls(rolls, num_rolls);

    // have to flush manually since we don't print newlines
    fflush(stdout);

    sleep_ms(100);
  }

  printf("\n");

  free(positions);
}

static void roll_wheels(int *const rolls, size_t num_rolls) {
  for (int i = 0; i < num_rolls; i++) {
    rolls[i] = roll_wheel();
  }
}

static bool poll_question(const char *const q) {
  printf("%s? y/n\n", q);

  char inp[5];
  fgets(inp, sizeof(inp), stdin);

  return inp[0] == 'y';
}

static struct roll_result run_once(int *const rolls, size_t num_rolls) {
  roll_wheels(rolls, num_rolls);
  render_rotating_rolls(rolls, num_rolls);

  // poll the user if they want to nudge a wheel
  if (poll_question("Nudge wheel")) {
    printf("select roll (0,%lu]:\n", num_rolls);
    char inp[30];
    fgets(inp, sizeof(inp), stdin);
    int roll = atoi(inp);

    if (roll < 0 || roll >= num_rolls) {
      puts("Invalid roll");
    }

    rolls[roll] = (rolls[roll] + 1) % NUM_SYMBOLS;

    puts("new result:");
    print_rolls(rolls, num_rolls);
    putchar('\n');
  }

  struct roll_result result = check_rolls(rolls, num_rolls);

  printf("matching symbols: %d, %s\n", result.matching_symbols,
         result_text[result.result]);

  return result;
}

static void print_stats(int *const stats, size_t num_rolls) {
  for (int i = 0; i < num_rolls; i++) {
    printf("%d: %d\n", i, stats[i]);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <rolls>\n", *argv);
    return 1;
  }

  size_t num_rolls = atoi(argv[1]);
  if (num_rolls <= 0) {
    fprintf(stderr, "At least 1 roll must be used.\n");
  }

  int *rolls = malloc(sizeof(int) * num_rolls);
  int *stats = calloc(num_rolls, sizeof(int));

  do {
    struct roll_result res = run_once(rolls, num_rolls);
    stats[res.matching_symbols]++;
  } while (poll_question("Play again"));

  puts("Game stats:");
  print_stats(stats, num_rolls);

  free(rolls);
  free(stats);
}
