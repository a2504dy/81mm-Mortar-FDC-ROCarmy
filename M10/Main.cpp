#include <iostream>
#include <cmath>

#define Pi (double)3.1415926

const double Radi = (Pi / 180.0);
const double Ratio_mil = (360.0 / 6400.0);

using namespace std;

class LinkedList;    // 為了將class LinkedList設成class CR的friend,需要先宣告

struct Obser_value
{
	double Ob_dir = 0, Ob_dist = 0;
};

class CR	//Collecting Report
{
private:
	// Data
	double distant, direct, dir;
	double x, y;
	// Next Pointer
	CR *next;

public:
	
	CR() :distant(0), direct(0), dir(0), x(0), y(0), next(NULL) {};
	CR(double a, double b) : distant(a), direct(b), dir(0), x(0), y(0), next(NULL) {};
	CR(double a, double b, double c) : distant(a), direct(b), dir(c), x(0), y(0), next(NULL) {};
	CR(double a, double b, double c, double d, double e) : distant(a), direct(b), dir(c), x(d), y(e), next(NULL) {};
	friend class LinkedList;
};

class LinkedList
{
private:
	int size;
	CR *Head;            // list的第一個node
	CR *Current;
public:
	LinkedList() :size(0), Head(NULL), Current(Head) {};
	
	void NewCR(double a1, double b1, double c1, double d1, double e1);			// 在list的尾巴新增node
	void ModiCR(double a1, double b1, double c1, double d1, double e1);
	void GetCoord(Obser_value *p);			// 提取座標
	void PrintCR();				// Print this node
	void PrintList();           // 印出list的所有資料
	void Clear();               // 把整串list刪除

};

void LinkedList::NewCR(double a1, double b1, double c1, double d1, double e1) 
{
	if (Head == NULL)
	{
		Current = new CR(a1, b1, c1, d1, e1);
		Head = Current;
	}
	else
	{
		Current->next = new CR(a1, b1, c1, d1, e1);
		Current = Current->next;
		if (Head->next == NULL)
			Head->next = Current;
	}
	
	size++;
}

void LinkedList::PrintCR()
{
	cout << "顯示射擊口令:" << endl;
	cout << "方位角 : " << Current->direct << "  ";
	cout << "方向 : " << Current->dir << "  ";
	cout << "距離 : " << Current->distant << endl;
	cout << "----地圖座標點----" << endl;
	cout << "X: " << Current->x << endl;
	cout << "Y: " << Current->y << endl;
}

void LinkedList::ModiCR(double a1, double b1, double c1, double d1, double e1)
{// distant direct dir x y
	Current->distant = a1;
	Current->direct = b1;
	Current->dir = c1;
	Current->x = d1;
	Current->y = e1;
}

void LinkedList::GetCoord(Obser_value *p)
{
	p->Ob_dir = Current->x;
	p->Ob_dist = Current->y;
}

void LinkedList::PrintList() {

	CR *previous = Head;
	if (Head == NULL)
		cout << "內容空白" << endl << endl;

	int temp = 1;
	while (previous) 
	{	
		if (temp == 1)
			cout << endl << "最初射擊口令:" << endl;
		else
			cout << endl << "第" << temp - 1 << "次" << "後續射擊口令:" << endl;
		cout << "方位角 : " << previous->direct << "  ";
		cout << "方向 : " << previous->dir << "  ";
		cout << "距離 : " << previous->distant << endl;
		cout << "----實際座標----" << endl;
		cout << "X: " << previous->x << endl;
		cout << "Y: " << previous->y << endl;

		previous = previous->next;
		temp++;
	}
	cout << endl;
}

void LinkedList::Clear() {

	while (Head) {
		Current = Head;
		Head = Head->next;
		delete Current;
		size--;
	}
}



void OB(Obser_value* p, double OT_dist);


int main()
{
	LinkedList List;
	Obser_value o;
	Obser_value Coord;
	double ot_a, ot_d, om_a, om_d, mt_a, mt_d;
	double o_x, o_y, t_x, t_y, m_x, m_y;
	o_x = 0; o_y = 0; t_x = 0; t_y = 0; m_x = 0; m_y = 0;
	
	cout << "圖解最初諸元" << endl << endl;
	cout << "請輸入 OT方位角" << endl;
	cout << "若要直接輸入MT方位角與距離請輸入 -1 :";
	cin >> ot_a;
	if (ot_a != -1)
	{
		cout << "請輸入OT距離 :";
		cin >> ot_d;
		cout << "請輸入OM方位角";
		cin >> om_a;
		cout << "請輸入OM距離 :";
		cin >> om_d;
		
		// Calculate MT
		o_x = -om_d * cos((90.0 - om_a * Ratio_mil) * Radi);
		o_y = -om_d * sin((90.0 - om_a * Ratio_mil) * Radi);

		t_x = ot_d * cos((90.0 - ot_a * Ratio_mil) * Radi) - (-o_x);
		t_y = ot_d * sin((90.0 - ot_a * Ratio_mil) * Radi) - (-o_y);

		mt_a = (atan2(t_x, t_y) / Radi) / Ratio_mil;
		if (mt_a < 0)
			mt_a = 6400 + mt_a;
		mt_d = pow(pow(t_x, 2) + pow(t_y, 2), 0.5);
	}
	else
	{
		cout << "請輸入MT方位角 :";
		cin >> mt_a;
		cout << "請輸入MT距離 :";
		cin >> mt_d;
		t_x = mt_d * cos((90.0 - mt_a * Ratio_mil) * Radi);
		t_y = mt_d * sin((90.0 - mt_a * Ratio_mil) * Radi);
	}
	
	List.NewCR(mt_d, mt_a, 0, t_x, t_y);
	List.PrintCR();
// part 2 Fire on Effect
	cout << "檢驗點試射或效力射" << endl;
		
	bool checkpoint = 1;
	while (checkpoint)
	{
		int sel = 0;
		cout << endl << "----請輸入----" << endl;
		cout << "效力射   : 0" << endl;
		cout << "觀測結果 : 1" << endl;
		cout << "修正報告 : 2" << endl;
		cin >> sel;
		
		// Calculate Target
		if (sel != 0)
		{
			if (ot_a == -1)
			{
				cout << "請輸入OT方位角與距離" << endl;
				cin >> ot_a;
				cin >> ot_d;
			}
			
			switch (sel)
			{
			case 1:
				OB(&o, ot_d);

				break;
			case 2:
				cout << "向右 (+) 向左 (-) :";
				cin >> o.Ob_dir;
				cout << "加多 (+) 減少 (-) :";
				cin >> o.Ob_dist;
				break;
			default:
				break;
			}
			cout << "修正報告: 向右(+)左(-) " << o.Ob_dir << " 加多(+)減少(-) " << o.Ob_dist << endl;
		// Calculate x,y
			double x, y;//C -s sC
			List.GetCoord(&Coord);
			x = Coord.Ob_dir + o.Ob_dir * cos((ot_a * Ratio_mil) * Radi) + o.Ob_dist * sin((ot_a * Ratio_mil) * Radi);
			y = Coord.Ob_dist - o.Ob_dir * sin((ot_a * Ratio_mil) * Radi) + o.Ob_dist * cos((ot_a * Ratio_mil) * Radi);
			
			double angle, distant;
			angle = (atan2(x, y) / Radi) / Ratio_mil;
				
			if (angle < 0)
				angle = 6400 + angle;
		
			distant = pow(pow(x, 2) + pow(y, 2), 0.5);

			List.NewCR(distant, angle, angle - mt_a, x, y);
			List.PrintCR();
		}
		
		
		cout << "繼續(0/1)" << endl;
		cin >> checkpoint;
	}
	List.PrintList();
}

void OB(Obser_value* p,double OT_dist)
{
	double dist, dir;
	static int time = 1;
	cout << "輸入觀測結果" << endl;
	cout << "遠彈(+) /近彈(-)  ";
	cin >> dist;
	cout << "偏右(+) /偏左(-)  ";
	cin >> dir;
	p->Ob_dir = -OT_dist / 1000 * dir;
	// bracketing method
	p->Ob_dist = 100 * pow(2,(ceil(OT_dist / 1000)-1)) * (-dist / abs(dist)) / time;
	time++;
}