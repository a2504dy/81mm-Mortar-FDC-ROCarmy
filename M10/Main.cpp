#include <iostream>
#include <cmath>

#define Pi (double)3.1415926

const double Radi = (Pi / 180.0);
const double Ratio_mil = (360.0 / 6400.0);

using namespace std;

class LinkedList;    // ���F�Nclass LinkedList�]��class CR��friend,�ݭn���ŧi

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
	CR *Head;            // list���Ĥ@��node
	CR *Current;
public:
	LinkedList() :size(0), Head(NULL), Current(Head) {};
	
	void NewCR(double a1, double b1, double c1, double d1, double e1);			// �blist�����ڷs�Wnode
	void ModiCR(double a1, double b1, double c1, double d1, double e1);
	void GetCoord(Obser_value *p);			// �����y��
	void PrintCR();				// Print this node
	void PrintList();           // �L�Xlist���Ҧ����
	void Clear();               // ����list�R��

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
	cout << "��ܮg���f�O:" << endl;
	cout << "��쨤 : " << Current->direct << "  ";
	cout << "��V : " << Current->dir << "  ";
	cout << "�Z�� : " << Current->distant << endl;
	cout << "----�a�Ϯy���I----" << endl;
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
		cout << "���e�ť�" << endl << endl;

	int temp = 1;
	while (previous) 
	{	
		if (temp == 1)
			cout << endl << "�̪�g���f�O:" << endl;
		else
			cout << endl << "��" << temp - 1 << "��" << "����g���f�O:" << endl;
		cout << "��쨤 : " << previous->direct << "  ";
		cout << "��V : " << previous->dir << "  ";
		cout << "�Z�� : " << previous->distant << endl;
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



void OB(Obser_value* p, double OT_dist);


int main()
{
	LinkedList List;
	Obser_value o;
	Obser_value Coord;
	double ot_a, ot_d, om_a, om_d, mt_a, mt_d;
	double o_x, o_y, t_x, t_y, m_x, m_y;
	o_x = 0; o_y = 0; t_x = 0; t_y = 0; m_x = 0; m_y = 0;
	
	cout << "�ϸѳ̪�Ѥ�" << endl << endl;
	cout << "�п�J OT��쨤" << endl;
	cout << "�Y�n������JMT��쨤�P�Z���п�J -1 :";
	cin >> ot_a;
	if (ot_a != -1)
	{
		cout << "�п�JOT�Z�� :";
		cin >> ot_d;
		cout << "�п�JOM��쨤";
		cin >> om_a;
		cout << "�п�JOM�Z�� :";
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
		cout << "�п�JMT��쨤 :";
		cin >> mt_a;
		cout << "�п�JMT�Z�� :";
		cin >> mt_d;
		t_x = mt_d * cos((90.0 - mt_a * Ratio_mil) * Radi);
		t_y = mt_d * sin((90.0 - mt_a * Ratio_mil) * Radi);
	}
	
	List.NewCR(mt_d, mt_a, 0, t_x, t_y);
	List.PrintCR();
// part 2 Fire on Effect
	cout << "�����I�ծg�ήĤO�g" << endl;
		
	bool checkpoint = 1;
	while (checkpoint)
	{
		int sel = 0;
		cout << endl << "----�п�J----" << endl;
		cout << "�ĤO�g   : 0" << endl;
		cout << "�[�����G : 1" << endl;
		cout << "�ץ����i : 2" << endl;
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
			
			switch (sel)
			{
			case 1:
				OB(&o, ot_d);

				break;
			case 2:
				cout << "�V�k (+) �V�� (-) :";
				cin >> o.Ob_dir;
				cout << "�[�h (+) ��� (-) :";
				cin >> o.Ob_dist;
				break;
			default:
				break;
			}
			cout << "�ץ����i: �V�k(+)��(-) " << o.Ob_dir << " �[�h(+)���(-) " << o.Ob_dist << endl;
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
		
		
		cout << "�~��(0/1)" << endl;
		cin >> checkpoint;
	}
	List.PrintList();
}

void OB(Obser_value* p,double OT_dist)
{
	double dist, dir;
	static int time = 1;
	cout << "��J�[�����G" << endl;
	cout << "���u(+) /��u(-)  ";
	cin >> dist;
	cout << "���k(+) /����(-)  ";
	cin >> dir;
	p->Ob_dir = -OT_dist / 1000 * dir;
	// bracketing method
	p->Ob_dist = 100 * pow(2,(ceil(OT_dist / 1000)-1)) * (-dist / abs(dist)) / time;
	time++;
}