#include <stdio.h>
#include <stdlib.h>

// tausche zwei Elemente im Array
void swap(int data[], int x1, int x2) {
  int temp = data[x1];
  data[x1] = data[x2];
  data[x2] = temp;
}

int partition(int data[], int l, int r, int* compare_cnt) {
  int piv = data[r];  // das letzte Element ist das Pivot
  int i = l - 1;      // die Position des letzten Elements >= Pivot
  int j = l;          // Durchlaufindex

  while (j < r) {
    (*compare_cnt)++;      // jeder Durchlauf == ein Vergleich
    if (data[j] >= piv) {  // falls Element >= Pivot -> Austausch
      i++;
      swap(data, i, j);
      j++;
    } else {  // sonst nichts passiert
      j++;
    }
  }

  // Es gilt: Pivot >= Pivot !!!
  i++;
  swap(data, i, r);

  return i;  // Position des Pivots wird zurückgegeben
}

void quick_sort(int data[], int l, int r, int* compare_cnt) {
  // Array der Länge >= 1 ist bereits sortiert
  if (l >= r) {
    return;
  }

  int pos = partition(data, l, r, compare_cnt);
  printf("%d ", data[pos]);                   // verwendete Pivot wird angezeigt
  quick_sort(data, l, pos - 1, compare_cnt);  // Quicksort handelt rekursiv
  quick_sort(data, pos + 1, r, compare_cnt);  // zuerst links, dann rechts
}

// Anzeige von Elementen des Arrays
void display_data(int data[], int n) {
  for (int i = 0; i < n; ++i) {
    printf("%d  ", data[i]);
  }
  printf("\n");
}

// leere das EingabePuffer
void buffer_leer() {
  int c;
  while ((c = getchar()) != EOF && c != '\n') {
  }
}

int main() {
  int n;     // Anzahl von Zahlen
  int* tab;  // Feld, das diese Zahlen enthält

  scanf("%d", &n);
  buffer_leer();  // das Puffer nach einer Lesenoperation leeren.

  // Speicherplatz für das Speichern der Zahlen wird allokiert
  tab = malloc(n * sizeof(int));
  if (tab == NULL) {
    fprintf(stderr, "Error: Out of memory!\n");  // Arbeitsspeicher voll
    exit(1);                                     // das Programm wird beendet
  }

  // Zeile mit n ganzen Zahlen wird eingelesen
  int len = 60;                             // initiale Größe des Feldes "line"
  char* line = malloc(len * sizeof(char));  // Feld zum Speichern der Zeile.
  int c;
  int i = 0;  // Anzahl von char im Feld "line"
  while ((c = getchar()) != EOF && c != '\n') {
    if (i >= len - 1) {  // es gibt mehr Char als die aktuelle Kapazität
      int new_len = 2 * len + 1;  // die Kapazität wird verdoppelt
      char* temp = realloc(line, new_len * sizeof(char));
      if (temp == NULL) {  // realloc gibt Fehler zurück ? -> Programm beendet!
        fprintf(stderr, "Error: Out of memory!\n");
        free(tab);
        exit(1);
      }
      line = temp;
      len = new_len;
    }
    line[i] = c;
    ++i;
  }
  line[i] = 0;  // das letzte Char ist '\0'

  // die Zahlen werden identifiziert.
  int j = 0;             // Anzahl von Zahlen bereits identifiziert
  int offset_total = 0;  // Anzahl von Char bereits bearbeitet
  int offset_relative;
  while (j < n) {
    if (line[offset_total] == 0) {  // überprufe das nächste Char
      // falls '\0', dann Ende der eingelesenen Zeile wird erreicht.
      // zu wenig Zahlen eingegeben : Error!!!
      fprintf(stderr, "Error: %d numbers expected, only %d numbers received\n",
              n, j);
      free(line);
      free(tab);
      exit(1);
    }

    // falls das Einlesen fehlschlägt, vielleicht unerwartete Eingabe
    if (sscanf((line + offset_total), "%d%n", &tab[j], &offset_relative) != 1) {
      fprintf(stderr, "Error: unexpected input\n");
      fprintf(stderr, "Error: %d numbers expected, only %d numbers received\n",
              n, j);
      free(line);
      free(tab);
      exit(1);
    }

    offset_total += offset_relative;
    ++j;
  }

  int count = 0;
  quick_sort(tab, 0, n - 1, &count);
  printf("\n");
  display_data(tab, n);
  printf("Used %d comparisons.\n", count);
  free(tab);
  free(line);
}
