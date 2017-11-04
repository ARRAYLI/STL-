/*

STL综合案例
		案例：学校演讲比赛
			1）某市举行一场演讲比赛，共有24个人参加，按参加顺序设置参赛号。比赛共三轮，前两轮为淘汰赛，第三轮为决赛。
			2）比赛方式：分组比赛
				第一轮分为4个小组，根据参赛号顺序依次划分，比如100-105为一组，106-111为第二组，依次类推，每组6个人，
			每人分别按参赛号顺序演讲。当小组演讲完后，淘汰组内排名最后的三个选手，然后继续下一个小组的比赛。
				第二轮分为2个小组，每组6人，每个人分别按参赛号顺序演讲。当小组完后，淘汰组内排名最后的三个选手，
			然后继续下一个小组的比赛。
				第三轮只剩下6个人，本轮为决赛，选出前三名。
				
			3)	选手每次要随机分组，进行比赛。
			4）比赛评分：10个评委打分，去除最低、最高分，求平均分
				每个选手演讲完由10个评委分别打分。该选手的最终得分是去掉一个最高分和一个最低分，求得剩下的8个成绩的平均分。
			选手的名次按得分降序排列，若得分一样，按参赛号升序排名。

		用STL编程，求解一下问题

			1）	请打印出所有选手的名字与参赛号，并以参赛号的升序排列。
			2）	打印每一轮比赛前，分组情况
			3）	打印每一轮比赛后，小组晋级名单
			4）	打印决赛前三名，选手名称、成绩。

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
#include<iterator>				// 输出流迭代器

const int PEOPLE_COUNT = 24;	// 总共有24位选手
const int JUDGE = 10;			// 总共有10个评委
const int SOCRE_NUM = 3;		// 每个人都有三轮成绩    第一轮  第二轮  第三轮
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

// 产生选手 得到第一轮选手的比赛名单
int  GenSpeaker(map<int, Speaker> &mapSpeaker, vector<int>  &v)
{
	string  str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	random_shuffle(str.begin(),str.end());

	for (int i=0;i<PEOPLE_COUNT;i++)
	{
		Speaker tmp;
		tmp.m_name = "选手";
		tmp.m_name += str[i];

	//	mapSpeaker.insert(map<int, Speaker>::value_type(100+i,tmp));
		mapSpeaker.insert(make_pair(100 + i, tmp));
	//	mapSpeaker.insert(pair<int,Speaker>(100+i,tmp));
	//	mapSpeaker[i + 100] = tmp;
	}
	for (int i=0;i<PEOPLE_COUNT;++i)
	{
		v.push_back(100+i);			// 参见比赛的人员
	}
	return 0;
}

// 选手抽签
int speach_contest_draw(vector<int> &v)
{
	random_shuffle(v.begin(),v.end());
	return 0;
}

// 选手比赛
int speach_contest(int index, vector<int> &v1, map<int, Speaker> &mapSpeaker, vector<int>  &v2)
{

	// 小组比赛得分，记录下来  求出 3名和后3 名
	multimap<int, int, greater<int>> mulmapGroup;		// 第一个 int 类型得分   第二个 int类型小组编号   第三个表示从大到小

	int tmpCount = 0;			// 分6组
	for (vector<int>::iterator it=v1.begin();it!=v1.end();++it)
	{
		tmpCount++;
		// 10个评委打分
		{
			// 定义一个双端队列，方便去除最高分，最低分，求平均分
			deque<int> descore;
			for (int i=0;i<JUDGE;++i)
			{
				int socre = rand() % 50 + 50;
				descore.push_back(socre);
			}
			
			sort(descore.begin(),descore.end());		// 对选手的10评委个得分排序
			descore.pop_front();						// 去掉最高分
			descore.pop_back();							// 去掉最低分
		
		   // 求平均分
			int socresum = accumulate(descore.begin(),descore.end(),0);			// 累加每个选手的总分
			int scoreavg = socresum / descore.size();	// 求平均分				
			mapSpeaker[*it].m_score[index] = scoreavg;  //  把选手的第一轮平均成绩 存入容器中
			mulmapGroup.insert(pair<int,int>(scoreavg,*it));
		}

		// 处理分组
		if (tmpCount%6 == 0)
		{
			cout << "\n小组比赛成绩为： \n" << endl;
			for (multimap<int, int, greater<int>>::iterator mit = mulmapGroup.begin(); mit != mulmapGroup.end(); ++mit)
			{
				// 编号   姓名   得分
				cout <<mit->second <<"\t"<<mapSpeaker[mit->second].m_name<<"\t" << mit->first<< endl;
			}

			// 前 3 名晋级
			while (mulmapGroup.size()>3)
			{
				multimap<int, int, greater<int>>::iterator it = mulmapGroup.begin();
				v2.push_back(it->second);				// 把前三名选手放到晋级名单中
				mulmapGroup.erase(it);					// 删除
			}
			mulmapGroup.clear();						// 清空  每小组晋级和退出比赛成绩
		}
	}

	return 0;
}

// 查看比赛结果
int speach_contest_print(int index,vector<int>  &v, map<int, Speaker> &mapSpeaker)
{
	cout << "\n第"<<index+1<< "  轮晋级的名单：\n" << endl;
	for (vector<int>::iterator it=v.begin();it!=v.end();++it)
	{
		cout <<"参赛编号：" <<*it <<"\t"<<"选手名字： "<<mapSpeaker[*it].m_name<<"\t"<<"选手得分："<<mapSpeaker[*it].m_score[index]<< endl;
	}
    cout << endl;

	return 0;
}

int main(void)
{
	// 容器的设计
	map<int, Speaker> mapSpeaker;		// 所有参加比赛的选手的信息
	vector<int> v1;						// 第 1 轮演讲比赛的名单
	vector<int> v2;						// 第 2 轮演讲比赛的名单
	vector<int> v3;						// 第 3 轮演讲比赛的名单
	vector<int> v4;						// 最后前 3 名  演讲比赛的名单

	// 产生选手  得到第一轮选手的比赛名单
	GenSpeaker(mapSpeaker,v1);

	cout << "按Enter键，开始第 1 轮比赛：" << endl;
	cin.get();			// 保留回车在输入流中

	// 第 1 轮  选手抽签  选手比赛    查看比赛结果
	speach_contest_draw(v1);								 // 选手抽签
	speach_contest(0,v1,mapSpeaker,v2);						 // 选手比赛
	speach_contest_print(0,v2,mapSpeaker);					 // 查看比赛结果


	cout << "按Enter键，开始第 2 轮比赛：" << endl;
	cin.get();			// 保留回车在输入流中
	// 第 2 轮  选手抽签  选手比赛    查看比赛结果
	speach_contest_draw(v2);								 // 选手抽签
	speach_contest(1, v2, mapSpeaker, v3);				     // 选手比赛
	speach_contest_print(1,v3, mapSpeaker);					 // 查看比赛结果

	cout << "按Enter键，开始第 3 轮比赛：" << endl;
	cin.get();			// 保留回车在输入流中
	// 第 3 轮  选手抽签  选手比赛    查看比赛结果
	speach_contest_draw(v3);								 // 选手抽签
	speach_contest(2, v3, mapSpeaker, v4);				     // 选手比赛
	speach_contest_print(2,v4, mapSpeaker);					 // 查看比赛结果
	
	return 0;
}