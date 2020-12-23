/* H[1] <= H[2] <= H[3] .... <= H[mid]  */
void Manacher(int s[], int len, int A[], int B[]) {
    int l = 0;
    A[l++] = -1;
    A[l++] = 0;
    for (int i = 0; i < len; i++) {
        A[l++] = s[i];
        A[l++] = 0;
    }
    A[l] = 0;
    int mx = 0, id = 0;
    for (int i = 0; i < l; i++) {
        B[i] = mx > i ? min(B[2*id-i], mx-i) : 1;
        while (A[i+B[i]] == A[i-B[i]]) {
            if (A[i-B[i]] != 0 && A[i-B[i]] > A[i-B[i]+2]) break;
            B[i]++;
        }
        if (i + B[i] > mx) mx = i+ B[i], id = i;
    }
}