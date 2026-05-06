#include <stdio.h>
#include <stdlib.h>

// Anzeige von Elementen des Arrays
void print_array(const int array[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

// Täusche die Position von
// zwei Elementen im Array
void swap(int data[], int i, int j) {
  int temp = data[i];
  data[i] = data[j];
  data[j] = temp;
}

// Setze Elemente an Positionen l und r
// auf ihre richtigen endgültigen Positionen
int* partition(int data[], int l, int r, int* compare_cnt) {
  if (data[l] < data[r]) {
    swap(data, l, r);
  }

  int p1 = data[l];  // die zwei Pivotelemente
  int p2 = data[r];  // p1 == data[l] == max von beiden Pivotelementen

  int i = l + 1;
  int k = r - 1;
  int j = i;

  while (j <= k) {
    (*compare_cnt)++;  // bei jeder Iteration um eins erhöhen
    if (data[j] > p1) {
      swap(data, j, i);
      i++;
      j++;
    } else if (data[j] < p2) {
      swap(data, j, k);
      k--;
    } else {
      j++;
    }
  }

  swap(data, l, i - 1);
  swap(data, r, k + 1);

  int* pivots = malloc(2 * sizeof(int));
  pivots[0] = i - 1;
  pivots[1] = k + 1;

  return pivots;  // gibt die neuen Positionen von
                  // beiden Pivotelementen zurück
}

// sortiere ein TeilArray mit Positionen l <= i <= r
void quick_sort(int data[], int l, int r, int* compare_cnt) {
  if (l >= r) {  // subArray bereits sortiert
    return;
  }

  // Pivotelemente werden an ihre richtigen Position gesetzt
  // Diese Positionen werden zurückgeholt, um weiter zu sortieren
  int* pivots = partition(data, l, r, compare_cnt);

  printf("%d %d ", data[pivots[0]],
         data[pivots[1]]);  // gebe die verwendete Pivots aus

  // die 3 SubArrays werden sortiert
  quick_sort(data, l, pivots[0] - 1, compare_cnt);
  quick_sort(data, pivots[0] + 1, pivots[1] - 1, compare_cnt);
  quick_sort(data, pivots[1] + 1, r, compare_cnt);

  free(pivots);  // Speicher freigeben
}

int main() {
  int compare_cnt = 0;
  int n;

  // Array für n int Elemente wird erstellt
  // Speicher wird allokiert
  scanf("%d", &n);
  int* arr = malloc(n * sizeof(int));

  // Array wird gefüllt
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  // Array wird sortiert
  int count = 0;
  quick_sort(arr, 0, n - 1, &count);
  printf("\n");

  // Array wird ausgegeben
  print_array(arr, n);
  printf("Used %d comparisons.\n", count);

  free(arr);  // Speicherplatz wird freigegeben
  return 0;
}