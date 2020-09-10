/*
    input
    10
    10 9 8 7 6 5 4 3 2 1
    output
    1 10 9 8 7 6 5 4 3 2
*/
int Min_show(int arr[], int n) {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (arr[(i + k) % n] == arr[(j + k) % n]) k++;
        else {
            if (arr[(i + k) % n] > arr[(j + k) % n]) i += k + 1;
            else j += k + 1;
            if (i == j)i++;
            k = 0;
        }
    }
    return min(i, j);
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int ans = Min_show(a,n);
    for (int i = 0; i < n; i++) printf("%d ", a[(i + ans) % n]);
}