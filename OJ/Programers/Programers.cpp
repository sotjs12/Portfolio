
/*
https://programmers.co.kr/learn/courses/30/lessons/42577
문제 설명
전화번호부에 적힌 전화번호 중, 한 번호가 다른 번호의 접두어인 경우가 있는지 확인하려 합니다.
전화번호가 다음과 같을 경우, 구조대 전화번호는 영석이의 전화번호의 접두사입니다.

구조대 : 119
박준영 : 97 674 223
지영석 : 11 9552 4421
전화번호부에 적힌 전화번호를 담은 배열 phone_book 이 solution 함수의 매개변수로 주어질 때, 어떤 번호가 다른 번호의 접두어인 경우가 있으면 false를 그렇지 않으면 true를 return 하도록 solution 함수를 작성해주세요.

제한 사항
phone_book의 길이는 1 이상 1,000,000 이하입니다.
각 전화번호의 길이는 1 이상 20 이하입니다.
같은 전화번호가 중복해서 들어있지 않습니다.
입출력 예제
phone_book	return
["119", "97674223", "1195524421"]	false
["123","456","789"]	true
["12","123","1235","567","88"]	false
입출력 예 설명
입출력 예 #1
앞에서 설명한 예와 같습니다.

입출력 예 #2
한 번호가 다른 번호의 접두사인 경우가 없으므로, 답은 true입니다.

입출력 예 #3
첫 번째 전화번호, “12”가 두 번째 전화번호 “123”의 접두사입니다. 따라서 답은 false입니다.

알림

2021년 3월 4일, 테스트 케이스가 변경되었습니다. 이로 인해 이전에 통과하던 코드가 더 이상 통과하지 않을 수 있습니다.
*/
// #include <string>
// #include <vector>
// #include <algorithm>
// using namespace std;

// bool solution_42577(vector<string> phone_book)
// {
//     bool answer = true;
//     sort(phone_book.begin(), phone_book.end());
//     for (int i = 0; i < phone_book.size() - 1; ++i)
//     {
//         if (phone_book[i + 1].rfind(phone_book[i], 0) == 0)
//         {
//             answer = false;
//             break;
//         }
//     }

//     return answer;
// }

/*
https://programmers.co.kr/learn/courses/30/lessons/42584?language=cpp
주식가격
문제 설명
초 단위로 기록된 주식가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를 return 하도록 solution 함수를 완성하세요.

제한사항
prices의 각 가격은 1 이상 10,000 이하인 자연수입니다.
prices의 길이는 2 이상 100,000 이하입니다.
입출력 예
prices	return
[1, 2, 3, 2, 3]	[4, 3, 1, 1, 0]
입출력 예 설명
1초 시점의 ₩1은 끝까지 가격이 떨어지지 않았습니다.
2초 시점의 ₩2은 끝까지 가격이 떨어지지 않았습니다.
3초 시점의 ₩3은 1초뒤에 가격이 떨어집니다. 따라서 1초간 가격이 떨어지지 않은 것으로 봅니다.
4초 시점의 ₩2은 1초간 가격이 떨어지지 않았습니다.
5초 시점의 ₩3은 0초간 가격이 떨어지지 않았습니다.
※ 공지 - 2019년 2월 28일 지문이 리뉴얼되었습니다.
*/

// #include <string>
// #include <vector>
// #include <stack>

// using namespace std;

// vector<int> solution(vector<int> prices)
// {
//     stack<int> stack;
//     int time = 0;
//     vector<int> answer(prices.size());
//     for (int price : prices)
//     {
//         while (!stack.empty() && prices[stack.top()] > price)
//         {
//             answer[stack.top()] = time - stack.top();
//             stack.pop();
//         }
//         stack.push(time);
//         time++;
//     }

//     while (!stack.empty())
//     {
//         answer[stack.top()] = time - stack.top() - 1;
//         stack.pop();
//     }
//     return answer;
// }

/*
https://programmers.co.kr/learn/courses/30/lessons/42626?language=cpp
더 맵게
문제 설명
매운 것을 좋아하는 Leo는 모든 음식의 스코빌 지수를 K 이상으로 만들고 싶습니다. 모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 Leo는 스코빌 지수가 가장 낮은 두 개의 음식을 아래와 같이 특별한 방법으로 섞어 새로운 음식을 만듭니다.

섞은 음식의 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두 번째로 맵지 않은 음식의 스코빌 지수 * 2)
Leo는 모든 음식의 스코빌 지수가 K 이상이 될 때까지 반복하여 섞습니다.
Leo가 가진 음식의 스코빌 지수를 담은 배열 scoville과 원하는 스코빌 지수 K가 주어질 때, 모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 섞어야 하는 최소 횟수를 return 하도록 solution 함수를 작성해주세요.

제한 사항
scoville의 길이는 2 이상 1,000,000 이하입니다.
K는 0 이상 1,000,000,000 이하입니다.
scoville의 원소는 각각 0 이상 1,000,000 이하입니다.
모든 음식의 스코빌 지수를 K 이상으로 만들 수 없는 경우에는 -1을 return 합니다.
입출력 예
scoville	K	return
[1, 2, 3, 9, 10, 12]	7	2
*/

// #include <string>
// #include <vector>
// #include <queue>

// using namespace std;

// int solution(vector<int> scoville, int K)
// {
//     int answer = 0;
//     priority_queue<int, vector<int>, greater<int> > pq;
//     for (int value : scoville)
//     {
//         pq.push(value);
//     }

//     int poped = 0;
//     while (!pq.empty())
//     {
//         poped = pq.top();
//         pq.pop();

//         if (poped >= K)
//             continue;
//         if (poped == 0 || pq.empty())
//         {
//             answer = -1;
//             break;
//         }
//         answer++;
//         poped = poped + (pq.top() * 2);
//         pq.pop();
//         pq.push(poped);
//     }
//     return answer;
// }

/*
https://programmers.co.kr/learn/courses/30/lessons/42627?language=cpp
디스크 컨트롤러
문제 설명
하드디스크는 한 번에 하나의 작업만 수행할 수 있습니다. 디스크 컨트롤러를 구현하는 방법은 여러 가지가 있습니다. 가장 일반적인 방법은 요청이 들어온 순서대로 처리하는 것입니다.
각 작업에 대해 [작업이 요청되는 시점, 작업의 소요시간]을 담은 2차원 배열 jobs가 매개변수로 주어질 때, 작업의 요청부터 종료까지 걸린 시간의 평균을 가장 줄이는 방법으로 처리하면 평균이 얼마가 되는지 return 하도록 solution 함수를 작성해주세요. (단, 소수점 이하의 수는 버립니다)

제한 사항
jobs의 길이는 1 이상 500 이하입니다.
jobs의 각 행은 하나의 작업에 대한 [작업이 요청되는 시점, 작업의 소요시간] 입니다.
각 작업에 대해 작업이 요청되는 시간은 0 이상 1,000 이하입니다.
각 작업에 대해 작업의 소요시간은 1 이상 1,000 이하입니다.
하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.
입출력 예
jobs	return
[[0, 3], [1, 9], [2, 6]]	9

*/

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>

// using namespace std;

// class comp
// {
// public:
//     bool operator()(const vector<int> &l, const vector<int> &r) const
//     {
//         return l[1] > r[1];
//     }
// };

// bool compareJob(const vector<int> &l, const vector<int> &r)
// {
//     return l[0] < r[0];
// }

// int solution(vector<vector<int> > jobs)
// {
//     int answer = 0;
//     int time = 0;
//     int size = jobs.size();
//     sort(jobs.begin(), jobs.end(), compareJob); //이게 필승 함정카드..
//     priority_queue<vector<int>, vector<vector<int> >, comp> pq;

//     for (vector<int> job : jobs)
//     {
//         while (!pq.empty() && job[0] > time)
//         {
//             time += pq.top()[1];
//             answer += time - pq.top()[0];
//             pq.pop();
//         }
//         if (job[0] >= time)
//             time = job[0];

//         pq.push(job);
//     }
//     while (!pq.empty())
//     {
//         time += pq.top()[1];
//         answer += time - pq.top()[0];
//         pq.pop();
//     }
//     return answer / size;
// }

/*
https://programmers.co.kr/learn/courses/30/lessons/42628?language=cpp
이중우선순위큐
문제 설명
이중 우선순위 큐는 다음 연산을 할 수 있는 자료구조를 말합니다.

명령어	수신 탑(높이)
I 숫자	큐에 주어진 숫자를 삽입합니다.
D 1	큐에서 최댓값을 삭제합니다.
D -1	큐에서 최솟값을 삭제합니다.
이중 우선순위 큐가 할 연산 operations가 매개변수로 주어질 때, 모든 연산을 처리한 후 큐가 비어있으면 [0,0] 비어있지 않으면 [최댓값, 최솟값]을 return 하도록 solution 함수를 구현해주세요.

제한사항
operations는 길이가 1 이상 1,000,000 이하인 문자열 배열입니다.
operations의 원소는 큐가 수행할 연산을 나타냅니다.
원소는 “명령어 데이터” 형식으로 주어집니다.- 최댓값/최솟값을 삭제하는 연산에서 최댓값/최솟값이 둘 이상인 경우, 하나만 삭제합니다.
빈 큐에 데이터를 삭제하라는 연산이 주어질 경우, 해당 연산은 무시합니다.
입출력 예
operations	return
["I 16","D 1"]	[0,0]
["I 7","I 5","I -5","D -1"]	[7,5]
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> operations)
{
    string operation;
    vector<int> answer;
    int value;

    for (auto op : operations)
    {
        operation = op.substr(0, 1);
        value = stoi(op.substr(2));

        if (operation == "I")
        {
            answer.insert(upper_bound(answer.begin(), answer.end(), value), value);
        }
        else if (!answer.empty())
        {
            if (value == 1)
                answer.erase(answer.end() - 1);
            else
                answer.erase(answer.begin());
        }
    }

    if (answer.empty())
        answer.push_back(0);
    return {answer.back(), answer.front()};
}

int main()
{
    auto result = solution({"I 16", "D 1"});
    cout << result[0] << "," << result[1] << endl;
    return 0;
}