# 4.10
```cpp
#include <stdio.h>
int main() {
  double f, c;
  scanf("%lf", &f);
  c = 5.0 / 9.0 * (f - 32);
  if (c > 40)
    printf("Hot\n");
  else if (c > 30)
    printf("Warm\n");
  else if (c > 20)
    printf("Room temperature\n");
  else if (c > 10)
    printf("Cool\n");
  else if (c > 0)
    printf("Cold\n");
  else
    printf("freezing\n");
}
```
# 4.11
```cpp
#include <stdio.h>
int main() {
  double x, y;
  printf("input x:");
  scanf("%lf\n", &x);
  if (x < 1000)
    y = x;
  else if (x >= 1000 && x < 2000)
    y = 0.9 * x;
  else if (x >= 2000 && x < 3000)
    y = 0.8 * x;
  else
    y = 0.7 * x;
  printf("x=%.2lf\n,y=%.2lf\n", x, y);
}
```

# 4.12
```cpp

```

# 4.13
```cpp
#include <stdio.h>
int main() {
  int h, m;
  printf("24 hour time:");
  scanf("%d%d", &h, &m);
  if (h > 24 || m > 60 || h < 0 || m < 0)
    printf("Input error.\n");
  else if (h <= 12)
    printf("12 hour time:%d:%02dAM\n,", h, m);
  else 
    printf("12 hour time:%d:%02dPM\n,", h - 12, m);
  return 0;
}
```

# 4.14
```cpp
#include <stdio.h>
int main() {
  int y1, m1, d1, y2 = 2022, m2, d2, age;
  printf("Input the birthday (yyyy-mm-dd):");
  scanf("%d%d%d", &y1, &m1, &d1);
  printf("Input the current day(yyyy-mm-dd)");
  if (m1 > m2)
    age = y2 - y1 - 1;
  else if (m1 < m2)
    age = y2 - y1;
  else if (d1 > d2)
    age = y2 - y1 - 1;
  else
    age = y2 - y1;
  printf("Age=%d\n", age);
  return 0;
}
```

# 4.15
```cpp
#include <stdio.h>
int main() {
  for (int i = 15; i <= 300; i += 15) printf("%d\n", i);
  return 0;
}
```

# 4.16
```cpp
#include <stdio.h>
int main() {
  int i = 0, x, maxi = -1e9, mini = 1e9, maxid = 0, minid = 0;
  while (~scanf("%d", &x)) {
    i++;
    if (maxi < x) {
      maxi = x;
      maxid = i;
    }
    if (mini > x) {
      mini = x;
      minid = i;
    }
  }
  printf("%d %d\n%d %d\n", maxi, maxid, mini, minid);
}
```

# 4.17
```cpp

```

# 4.18
```cpp
#include <stdio.h>
int main() {
  int i, n;
  long long t, s;
  t = 1, s = 0;
  printf("Please input n:");
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    t *= 7LL;
    s += t;
  }
  printf("%lld\n", s);
}
```

# 4.19
```cpp

```