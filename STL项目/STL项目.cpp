/*

STL�ۺϰ���
		������ѧУ�ݽ�����
			1��ĳ�о���һ���ݽ�����������24���˲μӣ����μ�˳�����ò����š����������֣�ǰ����Ϊ��̭����������Ϊ������
			2��������ʽ���������
				��һ�ַ�Ϊ4��С�飬���ݲ�����˳�����λ��֣�����100-105Ϊһ�飬106-111Ϊ�ڶ��飬�������ƣ�ÿ��6���ˣ�
			ÿ�˷ֱ𰴲�����˳���ݽ�����С���ݽ������̭����������������ѡ�֣�Ȼ�������һ��С��ı�����
				�ڶ��ַ�Ϊ2��С�飬ÿ��6�ˣ�ÿ���˷ֱ𰴲�����˳���ݽ�����С�������̭����������������ѡ�֣�
			Ȼ�������һ��С��ı�����
				������ֻʣ��6���ˣ�����Ϊ������ѡ��ǰ������
				
			3)	ѡ��ÿ��Ҫ������飬���б�����
			4���������֣�10����ί��֣�ȥ����͡���߷֣���ƽ����
				ÿ��ѡ���ݽ�����10����ί�ֱ��֡���ѡ�ֵ����յ÷���ȥ��һ����߷ֺ�һ����ͷ֣����ʣ�µ�8���ɼ���ƽ���֡�
			ѡ�ֵ����ΰ��÷ֽ������У����÷�һ����������������������

		��STL��̣����һ������

			1��	���ӡ������ѡ�ֵ�����������ţ����Բ����ŵ��������С�
			2��	��ӡÿһ�ֱ���ǰ���������
			3��	��ӡÿһ�ֱ�����С���������
			4��	��ӡ����ǰ������ѡ�����ơ��ɼ���

*/


#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
#include<numeric>
#include<functional>
#include<iterator>				// �����������

const int PEOPLE_COUNT = 24;	// �ܹ���24λѡ��
const int JUDGE = 10;			// �ܹ���10����ί
const int SOCRE_NUM = 3;		// ÿ���˶������ֳɼ�    ��һ��  �ڶ���  ������
using namespace std;

class Speaker
{
public:
	Speaker()
	{
		m_name = "";
		for (int i=0;i<SOCRE_NUM;++i)
		{
			m_score[i] = 0;
		}
	}
public:
	string m_name;
	int	   m_score[SOCRE_NUM];
};

// ����ѡ�� �õ���һ��ѡ�ֵı�������
int  GenSpeaker(map<int, Speaker> &mapSpeaker, vector<int>  &v)
{
	string  str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	random_shuffle(str.begin(),str.end());

	for (int i=0;i<PEOPLE_COUNT;i++)
	{
		Speaker tmp;
		tmp.m_name = "ѡ��";
		tmp.m_name += str[i];

	//	mapSpeaker.insert(map<int, Speaker>::value_type(100+i,tmp));
		mapSpeaker.insert(make_pair(100 + i, tmp));
	//	mapSpeaker.insert(pair<int,Speaker>(100+i,tmp));
	//	mapSpeaker[i + 100] = tmp;
	}
	for (int i=0;i<PEOPLE_COUNT;++i)
	{
		v.push_back(100+i);			// �μ���������Ա
	}
	return 0;
}

// ѡ�ֳ�ǩ
int speach_contest_draw(vector<int> &v)
{
	random_shuffle(v.begin(),v.end());
	return 0;
}

// ѡ�ֱ���
int speach_contest(int index, vector<int> &v1, map<int, Speaker> &mapSpeaker, vector<int>  &v2)
{

	// С������÷֣���¼����  ��� 3���ͺ�3 ��
	multimap<int, int, greater<int>> mulmapGroup;		// ��һ�� int ���͵÷�   �ڶ��� int����С����   ��������ʾ�Ӵ�С

	int tmpCount = 0;			// ��6��
	for (vector<int>::iterator it=v1.begin();it!=v1.end();++it)
	{
		tmpCount++;
		// 10����ί���
		{
			// ����һ��˫�˶��У�����ȥ����߷֣���ͷ֣���ƽ����
			deque<int> descore;
			for (int i=0;i<JUDGE;++i)
			{
				int socre = rand() % 50 + 50;
				descore.push_back(socre);
			}
			
			sort(descore.begin(),descore.end());		// ��ѡ�ֵ�10��ί���÷�����
			descore.pop_front();						// ȥ����߷�
			descore.pop_back();							// ȥ����ͷ�
		
		   // ��ƽ����
			int socresum = accumulate(descore.begin(),descore.end(),0);			// �ۼ�ÿ��ѡ�ֵ��ܷ�
			int scoreavg = socresum / descore.size();	// ��ƽ����				
			mapSpeaker[*it].m_score[index] = scoreavg;  //  ��ѡ�ֵĵ�һ��ƽ���ɼ� ����������
			mulmapGroup.insert(pair<int,int>(scoreavg,*it));
		}

		// �������
		if (tmpCount%6 == 0)
		{
			cout << "\nС������ɼ�Ϊ�� \n" << endl;
			for (multimap<int, int, greater<int>>::iterator mit = mulmapGroup.begin(); mit != mulmapGroup.end(); ++mit)
			{
				// ���   ����   �÷�
				cout <<mit->second <<"\t"<<mapSpeaker[mit->second].m_name<<"\t" << mit->first<< endl;
			}

			// ǰ 3 ������
			while (mulmapGroup.size()>3)
			{
				multimap<int, int, greater<int>>::iterator it = mulmapGroup.begin();
				v2.push_back(it->second);				// ��ǰ����ѡ�ַŵ�����������
				mulmapGroup.erase(it);					// ɾ��
			}
			mulmapGroup.clear();						// ���  ÿС��������˳������ɼ�
		}
	}

	return 0;
}

// �鿴�������
int speach_contest_print(int index,vector<int>  &v, map<int, Speaker> &mapSpeaker)
{
	cout << "\n��"<<index+1<< "  �ֽ�����������\n" << endl;
	for (vector<int>::iterator it=v.begin();it!=v.end();++it)
	{
		cout <<"������ţ�" <<*it <<"\t"<<"ѡ�����֣� "<<mapSpeaker[*it].m_name<<"\t"<<"ѡ�ֵ÷֣�"<<mapSpeaker[*it].m_score[index]<< endl;
	}
    cout << endl;

	return 0;
}

int main(void)
{
	// ���������
	map<int, Speaker> mapSpeaker;		// ���вμӱ�����ѡ�ֵ���Ϣ
	vector<int> v1;						// �� 1 ���ݽ�����������
	vector<int> v2;						// �� 2 ���ݽ�����������
	vector<int> v3;						// �� 3 ���ݽ�����������
	vector<int> v4;						// ���ǰ 3 ��  �ݽ�����������

	// ����ѡ��  �õ���һ��ѡ�ֵı�������
	GenSpeaker(mapSpeaker,v1);

	cout << "��Enter������ʼ�� 1 �ֱ�����" << endl;
	cin.get();			// �����س�����������

	// �� 1 ��  ѡ�ֳ�ǩ  ѡ�ֱ���    �鿴�������
	speach_contest_draw(v1);								 // ѡ�ֳ�ǩ
	speach_contest(0,v1,mapSpeaker,v2);						 // ѡ�ֱ���
	speach_contest_print(0,v2,mapSpeaker);					 // �鿴�������


	cout << "��Enter������ʼ�� 2 �ֱ�����" << endl;
	cin.get();			// �����س�����������
	// �� 2 ��  ѡ�ֳ�ǩ  ѡ�ֱ���    �鿴�������
	speach_contest_draw(v2);								 // ѡ�ֳ�ǩ
	speach_contest(1, v2, mapSpeaker, v3);				     // ѡ�ֱ���
	speach_contest_print(1,v3, mapSpeaker);					 // �鿴�������

	cout << "��Enter������ʼ�� 3 �ֱ�����" << endl;
	cin.get();			// �����س�����������
	// �� 3 ��  ѡ�ֳ�ǩ  ѡ�ֱ���    �鿴�������
	speach_contest_draw(v3);								 // ѡ�ֳ�ǩ
	speach_contest(2, v3, mapSpeaker, v4);				     // ѡ�ֱ���
	speach_contest_print(2,v4, mapSpeaker);					 // �鿴�������
	
	return 0;
}