#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

int stringmatching(char *text, char *pattern, int n, int m) {
    count = 0;
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m) {
            count++;
            if (pattern[j] != text[i + j]) {
                break;
            }
            j++;
        }
        if (j == m) {
            return count;
        }
    }
    return count;
}

void plotter() {
    FILE *f1 = fopen("stringbest.txt", "a");
    FILE *f2 = fopen("stringworst.txt", "a");
    FILE *f3 = fopen("stringavg.txt", "a");

    char *text = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 1000; i++) {
        text[i] = 'a'; // Initialize the text array with 'a'
    }

    int m = 10, n = 1000;

    while (m <= 1000) {
        char *pattern = (char *)malloc(m * sizeof(char));

        // Best Case: All characters match
        for (int i = 0; i < m; i++) {
            pattern[i] = 'a';
        }
        count = 0;
        stringmatching(text, pattern, n, m);
        fprintf(f1, "%d\t%d\n", m, count);

        // Worst Case: Last character differs
        pattern[m - 1] = 'b';
        count = 0;
        stringmatching(text, pattern, n, m);
        fprintf(f2, "%d\t%d\n", m, count);

        // Average Case: Random characters
        for (int i = 0; i < m; i++) {
            pattern[i] = 'a' + rand() % 3; // Random 'a', 'b', or 'c'
        }
        count = 0;
        stringmatching(text, pattern, n, m);
        fprintf(f3, "%d\t%d\n", m, count);

        free(pattern);

        if (m < 100) {
            m += 10;
        } else {
            m += 100;
        }
    }

    free(text);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

int main() {
    plotter();
    return 0;
}