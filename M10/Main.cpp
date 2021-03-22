#include <iostream>
#include <cmath>

#define Pi (double)3.1415926

const double Radi = (Pi / 180.0);
const double Ratio_mil = (360.0 / 6400.0);

using namespace std;

class LinkedList;    // ���F�Nclass LinkedList�]��class CR��friend,�ݭn���ŧi

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
	CR *Head;            // list���Ĥ@��node
	CR *Current;
public:
	LinkedList() :size(0), Head(NULL), Current(Head) {};
	
	void NewCR(double a1, double b1, double c1, double d1);			// �blist�����ڷs�Wnode
	void ModiCR(double a1, double b1, double c1, double d1);
	void PrintCR();			// Print this node
	void PrintList();           // �L�Xlist���Ҧ����
	void Clear();               // ����list�R��

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
	cout << "��ܭץ����i:" << endl;
	cout << "��V : " << Current->dir << "  ";
	cout << "�Z�� : " << Current->dist << endl;
	cout << "----��ڮy��----" << endl;
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
		cout << "���e�ť�" << endl << endl;

	int temp = 1;
	while (previous) 
	{	
		cout << endl << "��" << temp << "��" << "�ץ����i:" << endl;
		cout << "��V : " << previous->dir << "  ";
		cout << "�Z�� : " << previous->dist << endl;
		cout << "----��ڮy��----" << endl;
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
	
	
	cout << "�п�JOT��쨤�P�Z��" << endl;
	cout << "�Y�L�п�J-1" << endl;
	cin >> ot_a;
	if (ot_a != -1)
	{
		cin >> ot_d;
		cout << "�п�JOM��쨤�P�Z��" << endl;
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
		cout << "�п�JMT��쨤�P�Z��" << endl;
		cin >> mt_a;
		cin >> mt_d;
	}
	
	cout << "MT��쨤: " << mt_a << endl;
	cout << "MT�Z��: " << mt_d << endl;
	//test
	cout << "x: " << t_x << "  y: " << t_y << endl;
// part 2 Fire on Effect
	cout << "�����I�ծg" << endl;
	
	LinkedList List;
	
	bool checkpoint = 1;
	while (checkpoint)
	{
		int sel = 0;
		cout << endl << "----�п�J----" << endl << "�ĤO�g:0" << endl << "�[�����G:1" << endl << "�ץ����i:2" << endl;
		cin >> sel;
		
		// Calculate Target
		if (sel != 0)
		{
			if (ot_a == -1)
			{
				cout << "�п�JOT��쨤�P�Z��" << endl;
				cin >> ot_a;
				cin >> ot_d;
			}
			double OB_distant, OB_direction;
			double OB_C_dir, OB_C_dist;

			switch (sel)
			{
			case 1:
				cout << "�� + �� - :" << endl;
				cin >> OB_distant;
				cout << "�k + �� - :" << endl;
				cin >> OB_direction;

				// Calculate the correcting report
				OB_C_dir = -ot_d / 1000 * OB_direction;
				OB_C_dist = -ot_d / 1000 * OB_distant;

				break;
			case 2:
				cout << "�V�k + �V�� - :" << endl;
				cin >> OB_C_dir;
				cout << "�[�h + ��� - :" << endl;
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
			cout << "����g���f�O: ��쨤 " << aa << " ��V " << aa - mt_a << " �Z�� " << dd << endl;

		}

		
		cout << "�~��(0/1)" << endl;
		cin >> checkpoint;		
	}
	
}