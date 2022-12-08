/**
Co N chi tiet may can duoc gia cong lan luot tren hai may A va B. Thoi gian gia cong chi tiet i tren may A la a_i, thoi gian gia cong tren may B la b_i.
Yeu cau: Hay tim trinh tu gia cong cac chi tiet tren hai may sao cho viec hoan thanh gia cong tat ca cac chi tiet la som nhat co the.
**/
struct job{
  int x, y, pos;
} a[N], b[N];

int tmp[N], timeA, timeB;

void do_job(job *v, int bound){
  for(int i = 1; i <= bound; i++){
    timeA += v[i].x;
    timeB = max(timeB, timeA) + v[i].y;
  }
}

int main(){
  int n;
  cin >> n;

  for(int i = 1; i <= n; i++)
    cin >> tmp[i];

  int n1 = 0, n2 = 0;
  for(int i = 1, y; i <= n; i++){
    cin >> y;
    if(tmp[i] <= y)
      a[++n1] = {tmp[i], y, i};
    else
      b[++n2] = {tmp[i], y, i};
  }

  sort(a + 1, a + 1 + n1, [](const job &x1, const job &x2){
    return x1.x < x2.x;
  });
  sort(b + 1, b + 1 + n2, [](const job &x1, const job &x2){
    return x1.y > x2.y;
  });

  do_job(a, n1);
  do_job(b, n2);

  cout << timeB << '\n';
  for(int i = 1; i <= n1; i++)
    cout << a[i].pos << ' ';
  for(int i = 1; i <= n2; i++)
    cout << b[i].pos << ' ';
}
