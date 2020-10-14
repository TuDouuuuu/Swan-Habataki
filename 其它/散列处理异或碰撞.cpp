ull Newrnd() {
    return ((ull) rand() << 45) | ((ull) rand() << 30) | (rand() << 15) | rand();
}
int main() {
    srand(114514);  // random
}