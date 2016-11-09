# ZOND*
Allows to **trace memory** dynamically (*prototype, alpha version*).

\**The project named after the Soviet ["Zond"](https://en.wikipedia.org/wiki/Zond_3) mission*

## Limitations
* For only **LLVM-IR** code, translated from **C** (by **clang**).
* Tracks only variables allocated in the **stack**, not in the *heap* (via malloca/free).
* Supports only **integers** (char, short, int, long) and single-dimensional **integer arrays**.
* No global variables support.

## Example
It the following example the **target** procedure *main* allocates memory for array and then changes it step by step via *change* procedure.
```C
void change(int arr[], int idx, int val) {
  arr[idx] = val;
}

int main () {
  int arr[] = {1,2,3,4}; goto L;
 L:  change(arr, 0, 5);
  change(arr, 1, 6);
  change(arr, 2, 7);
  change(arr, 3, 8);
}
```
The **trace** is:
```
 #frame 0: {1,2,3,4} 
 #frame 0: {5,2,3,4}  #frame 1: 5 0 
 #frame 0: {5,6,3,4}  #frame 1: 6 1 
 #frame 0: {5,6,7,4}  #frame 1: 7 2 
 #frame 0: {5,6,7,8}  #frame 1: 8 3 
 #frame 0: {5,6,7,8} 
```
