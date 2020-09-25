/*
    input               output
    ababa               2 4 5
    ababa = ab + ab + a
    bbababaabaaabaaaab  1 2 4 6 9 13 18
    bbababaabaaabaaaab
    = b + b + ab + ab + aab + aaaab + aaaab
*/
vector<int> Lyndon_Arr; // 分解后的串的右端点
// call: Lyndon_Word(str, strlen(str+1));
void Lyndon_Word(char s[], int s_len) {
    int i = 1;
    while (i <= s_len) {
        int j = i, k = j + 1;
        while (k <= s_len && s[j] <= s[k]) {
            if (s[j] < s[k]) j = i;
            else j++;
            k++;
        }
        while (i <= j) {
            Lyndon_Arr.push_back(i-j+k-1);
            i += k - j;
        }
    }
}