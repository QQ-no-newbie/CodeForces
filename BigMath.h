#include <string.h>

#include <algorithm>
#include <iostream>
using namespace std;

class Bignum {
 public:
  bool ispos = 1;
  string PartInt = "", PartDecimal = "";

  Bignum(string a) {
    int begin = 0;
    if (a[begin] == '-') ispos = 0, begin++;
    int dec = a.find('.');
    if (dec < a.length()) {
      PartInt = a.substr(begin, dec - begin);
      PartDecimal = a.substr(dec + 1, a.length() - dec);
    } else
      PartInt = a.substr(begin, a.length() - begin);
  }
};

string Big_Add(string, string);
string Big_Sub(string, string);
string Big_Mul(string, string);
string Big_Div(string, string);

string Big_Add(string x, string y) {
  Bignum a = Bignum(x);
  Bignum b = Bignum(y);

  if (a.ispos != b.ispos) {
    if (a.ispos)
      return Big_Sub(x, y.substr(1, y.length() - 1));
    else {
      string res = Big_Sub(x.substr(1, x.length() - 1), y);
      if (res[0] == '-')
        return res.substr(1, res.length() - 1);
      else
        return '-' + res;
    }
  }

  string resD, resI;

  // 小数部分加法
  int maxlen = max(a.PartDecimal.length(), b.PartDecimal.length()), carry = 0;
  for (int i = 0; i < maxlen; i++) {
    if (i >= a.PartDecimal.length()) a.PartDecimal.push_back('0');
    if (i >= b.PartDecimal.length()) b.PartDecimal.push_back('0');
  }
  for (int i = maxlen - 1; i >= 0; i--) {
    int t = carry + a.PartDecimal[i] - '0' + b.PartDecimal[i] - '0';
    resD.push_back(t % 10 + '0');
    carry = t / 10;
  }

  // 整数部分
  string n = a.PartInt, m = b.PartInt;

  reverse(n.begin(), n.end());
  reverse(m.begin(), m.end());
  maxlen = max(n.length(), m.length());
  for (int i = 0; i < maxlen; i++) {
    if (i >= n.length()) n.push_back('0');
    if (i >= m.length()) m.push_back('0');
  }
  for (int i = 0; i < maxlen; i++) {
    int t = carry + n[i] - '0' + m[i] - '0';
    resI.push_back(t % 10 + '0');
    carry = t / 10;
  }
  if (carry != 0) resI.push_back(carry + '0');
  reverse(resI.begin(), resI.end());
  reverse(resD.begin(), resD.end());
  string res = a.ispos ? resI : "-" + resI;
  res += ((resD.length() == 0) ? "" : ('.' + resD));

  return res;
}

int Big_com(Bignum a, Bignum b) {
  // 不考虑正负号
  // 相等返回0， a大返回1， b大返回-1
  int res = 1;
  if (a.PartInt.length() > b.PartInt.length())
    return res;
  else if (a.PartInt.length() < b.PartInt.length())
    return -res;
  else {
    if (a.PartInt > b.PartInt)
      return res;
    else if (a.PartInt < b.PartInt)
      return -res;
    else {
      if (a.PartDecimal > b.PartDecimal)
        return 1;
      else if (a.PartDecimal < b.PartDecimal)
        return -1;
      else
        return 0;
    }
  }
}

string Big_Sub(string x, string y) {
  Bignum a = Bignum(x);
  Bignum b = Bignum(y);

  if (a.ispos != b.ispos) {
    if (a.ispos)
      return Big_Add(x, y.substr(1, y.length() - 1));
    else
      return '-' + Big_Add(x.substr(1, x.length() - 1), y);
  }

  // ispos = 1 表示大于0 ，= -1是小于0
  int ispos = a.ispos ? 1 : -1, com = Big_com(a, b);
  if (com <= 0) {
    if (com)
      ispos *= -1, swap(a, b);
    else
      return "0";
  }

  // 补前导0和后导0
  string n, m;
  n = a.PartDecimal, m = b.PartDecimal;
  int maxlen = max(n.length(), m.length());
  int lenDecimal = maxlen;
  for (int i = 0; i < maxlen; i++) {
    if (i >= n.length()) n.push_back('0');
    if (i >= m.length()) m.push_back('0');
  }
  reverse(n.begin(), n.end());
  reverse(m.begin(), m.end());
  reverse(a.PartInt.begin(), a.PartInt.end());
  reverse(b.PartInt.begin(), b.PartInt.end());
  n += a.PartInt;
  m += b.PartInt;
  maxlen = max(n.length(), m.length());
  for (int i = 0; i < maxlen; i++) {
    if (i >= n.length()) n.push_back('0');
    if (i >= m.length()) m.push_back('0');
  }

  // 计算部分
  string res;
  int carry = 0;
  for (int i = 0; i < maxlen; i++) {
    int t = n[i] - m[i] - carry;
    if (t < 0) t += 10, carry = 1;
    res.push_back(t + '0');
  }
  if (lenDecimal)
    res = res.substr(0, lenDecimal) + '.' +
          res.substr(lenDecimal, res.length() - lenDecimal);
  reverse(res.begin(), res.end());
  for (int i = 0; i < res.length(); i++) {
    if (res[i] - '0') {
      if (ispos > 0)
        return res.substr(i, res.length() - i);
      else
        return "-" + res.substr(i, res.length() - i);
    }
  }
  return res;
}

string Add(string x, string y) {
  reverse(x.begin(), x.end());
  reverse(y.begin(), y.end());
  string res = Big_Add(x, y);
  reverse(res.begin(), res.end());
  return res;
}

string Mul(string x, int y) {
  // x为倒序
  string res;
  int carry = 0, bits = 0;
  while (y >= 10) {
    res.push_back('0');
    y /= 10;
  }
  for (int i = 0; i < x.length(); i++) {
    int t = (x[i] - '0') * y + carry;
    res.push_back(t % 10 + '0');
    carry = t / 10;
  }
  return res;
}

string Big_Mul(string x, string y) {
  Bignum a = Bignum(x);
  Bignum b = Bignum(y);

  // 补前导0和后导0
  string n, m;
  n = a.PartDecimal, m = b.PartDecimal;
  int maxlen = max(n.length(), m.length());
  int lenDecimal = maxlen * 2;
  for (int i = 0; i < maxlen; i++) {
    if (i >= n.length()) n.push_back('0');
    if (i >= m.length()) m.push_back('0');
  }
  reverse(n.begin(), n.end());
  reverse(m.begin(), m.end());
  reverse(a.PartInt.begin(), a.PartInt.end());
  reverse(b.PartInt.begin(), b.PartInt.end());
  n += a.PartInt;
  m += b.PartInt;
  maxlen = max(n.length(), m.length());
  for (int i = 0; i < maxlen; i++) {
    if (i >= n.length()) n.push_back('0');
    if (i >= m.length()) m.push_back('0');
  }

  // 计算部分
  string res = "0";
  for (int i = 0; i < maxlen; i++) {
    int t = m[i] - '0';
    for (int j = 0; j < i; j++) t *= 10;
    res = Add(res, Mul(n, t));
  }

  //去除前后导0
  if (lenDecimal) {
    res = res.substr(0, lenDecimal) + '.' +
          res.substr(lenDecimal, res.length() - lenDecimal);
    int i = 0, j = res.length() - 1;
    while (res[i] == '0' || res[i] == '.') i++;
    while (res[j] == '0' && res[j - 1] != '.') j--;
    if (res[j] == '.') res.push_back('0'), j++;
    if (i == j)
      res = "0";
    else
      res = res.substr(i, j - i + 1);
    reverse(res.begin(), res.end());
  } else {
    int i = res.length() - 1;
    for (; i >= 0; i--)
      if (res[i] != '0') {
        res = res.substr(0, i + 1);
        break;
      }
    if (i < 0)
      res = "0";
    else
      reverse(res.begin(), res.end());
  }
  if (a.ispos == b.ispos)
    return res;
  else
    return "-" + res;
}

string Big_Div(string x, string y) {
  int ispos = 1;
  if (x[0] == '-') ispos *= -1, x = x.substr(1, x.length() - 1);
  if (y[0] == '-') ispos *= -1, y = y.substr(1, y.length() - 1);

  Bignum a = Bignum(x);
  Bignum b = Bignum(y);

  int maxlen = max(a.PartDecimal.length(), b.PartDecimal.length());
  for (int i = 0; i < maxlen; i++) {
    if (i >= a.PartDecimal.length()) a.PartDecimal.push_back('0');
    if (i >= b.PartDecimal.length()) b.PartDecimal.push_back('0');
  }

  string n = a.PartInt + a.PartDecimal;
  string m = b.PartInt + b.PartDecimal;

  if (!Big_com(n, m)) return "1";

  int i = 0, dec = 0;
  string res, div;
  div.push_back(n[i++]);
  while (Big_com(div, m) < 0 && dec < 10) {
    if (i >= n.length()) {
      i++, dec++;
      if (res.length() == 0)
        res += "0.";
      else
        res.push_back('0');
      if (div != "0") div.push_back('0');
    } else
      div.push_back(n[i++]);
  }

  while (dec < 10) {
    int quo = 0;
    while (Big_com(div, m) >= 0) {
      div = Big_Sub(div, m);
      quo++;
    }
    res.push_back(quo + '0');
    if (i >= n.length()) {
      if (div != "0") {
        if (!dec) {
          if (res.length() == 0) res.push_back('0');
          res.push_back('.');
        } 
        div.push_back('0');
      } else break;
      dec++;
    } else
      div.push_back(n[i++]);
  }

  if (ispos)
    return res;
  else
    return "-" + res;
}