#include <iostream>
#include <cmath>

#define Pi (double)3.1415926

const double Radi = (Pi / 180.0);
const double Ratio_mil = (360.0 / 6400.0);

using namespace std;

class LinkedList;    // 為了將class LinkedList設成class CR的friend,需要先宣告

class CR	//Collecting Report
{
private:
	// Data
	double dist, dir;
	double x, y;
	// Next Pointer
	CR *next;

public:
	
	CR() :dist(0), dir(0), x(0), y(0), next(NULL) {};
	CR(double a, double b) : dist(a), dir(b), x(0), y(0), next(NULL) {};
	CR(double a, double b, double c, double d) : dist(a), dir(b), x(c), y(d), next(NULL) {};
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
	
	void NewCR(double a1, double b1, double c1, double d1);			// 在list的尾巴新增node
	void ModiCR(double a1, double b1, double c1, double d1);
	void PrintCR();			// Print this node
	void PrintList();           // 印出list的所有資料
	void Clear();               // 把整串list刪除

};

void LinkedList::NewCR(double a1, double b1, double c1, double d1) 
{
	if (Head == NULL)
	{
		Current = new CR(a1, b1, c1, d1);
		Head = Current;
	}
	else
	{
		Current->next = new CR(a1,b1,c1,d1);
		Current = Current->next;
		if (Head->next == NULL)
			Head->next = Current;
	}
	
	
	size++;
}

void LinkedList::PrintCR()
{
	cout << "顯示修正報告:" << endl;
	cout << "方向 : " << Current->dir << "  ";
	cout << "距離 : " << Current->dist << endl;
	cout << "----實際座標----" << endl;
	cout << "X: " << Current->x << endl;
	cout << "Y: " << Current->y << endl;
}

void LinkedList::ModiCR(double a1, double b1, double c1, double d1)
{
	Current->dist = a1;
	Current->dir = b1;
	Current->x = c1;
	Current->y = d1;
}

void LinkedList::PrintList() {

	CR *previous = Head;
	if (Head == NULL)
		cout << "內容空白" << endl << endl;

	int temp = 1;
	while (previous) 
	{	
		cout << endl << "第" << temp << "次" << "修正報告:" << endl;
		cout << "方向 : " << previous->dir << "  ";
		cout << "距離 : " << previous->dist << endl;
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

int main()
{
	double ot_a, ot_d, om_a, om_d, mt_a, mt_d;
	double o_x, o_y, t_x, t_y, m_x, m_y;
	o_x = 0; o_y = 0; t_x = 0; t_y = 0; m_x = 0; m_y = 0;
	
	
	cout << "請輸入OT方位角與距離" << endl;
	cout << "若無請輸入-1" << endl;
	cin >> ot_a;
	if (ot_a != -1)
	{
		cin >> ot_d;
		cout << "請輸入OM方位角與距離" << endl;
		cin >> om_a;
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
		cout << "請輸入MT方位角與距離" << endl;
		cin >> mt_a;
		cin >> mt_d;
	}
	
	cout << "MT方位角: " << mt_a << endl;
	cout << "MT距離: " << mt_d << endl;
	//test
	cout << "x: " << t_x << "  y: " << t_y << endl;
// part 2 Fire on Effect
	cout << "檢驗點試射" << endl;
	
	LinkedList List;
	
	bool checkpoint = 1;
	while (checkpoint)
	{
		int sel = 0;
		cout << endl << "----請輸入----" << endl << "效力射:0" << endl << "觀測結果:1" << endl << "修正報告:2" << endl;
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
			double OB_distant, OB_direction;
			double OB_C_dir, OB_C_dist;

			switch (sel)
			{
			case 1:
				cout << "遠 + 近 - :" << endl;
				cin >> OB_distant;
				cout << "右 + 左 - :" << endl;
				cin >> OB_direction;

				// Calculate the correcting report
				OB_C_dir = -ot_d / 1000 * OB_direction;
				OB_C_dist = -ot_d / 1000 * OB_distant;

				break;
			case 2:
				cout << "向右 + 向左 - :" << endl;
				cin >> OB_C_dir;
				cout << "加多 + 減少 - :" << endl;
				cin >> OB_C_dist;
				break;
			default:
				break;
			}
			
		// Calculate x,y
			double x, y;//C -s sC
			//test
			double x1, y1;
			
				x1= OB_C_dir * cos((ot_a * Ratio_mil) * Radi) - OB_C_dist * sin((ot_a * Ratio_mil) * Radi);
				x = t_x - x1;
				y1 = OB_C_dir * sin((ot_a * Ratio_mil) * Radi) + OB_C_dist * cos((ot_a * Ratio_mil) * Radi);
				y = t_y + y1;
				cout << "delta x:" << x1 << endl;
				cout << "delta y:" << y1 << endl;
			double aa, dd;
			aa = (atan2(x, y) / Radi) / Ratio_mil;
			if (aa < 0)
				aa = 6400 + mt_a;
			dd = pow(pow(x, 2) + pow(y, 2), 0.5);


			List.NewCR(OB_C_dist, OB_C_dir, x, y);
			//List.PrintList();
			List.PrintCR();
			cout << "後續射擊口令: 方位角 " << aa << " 方向 " << aa - mt_a << " 距離 " << dd << endl;

		}

		
		cout << "繼續(0/1)" << endl;
		cin >> checkpoint;		
	}
	
}