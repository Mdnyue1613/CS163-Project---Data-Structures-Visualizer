#include "../header/PRandom.h"

PRandom::PRandom(void) {
    gen = mt19937(rd());
}

int PRandom::random(int From, int To) {
    uniform_int_distribution<int> distr(From, To);
    return distr(gen);
}