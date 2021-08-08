
#include <iostream>

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

#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices)
{
    stack<int> stack;
    int time = 0;
    vector<int> answer(prices.size());
    for (int price : prices)
    {
        while (!stack.empty() && prices[stack.top()] > price)
        {
            answer[stack.top()] = time - stack.top();
            stack.pop();
        }
        stack.push(time);
        time++;
    }

    while (!stack.empty())
    {
        answer[stack.top()] = time - stack.top() - 1;
        stack.pop();
    }
    return answer;
}

int main()
{
    vector<int> prices = {1, 2, 3, 2, 3};
    vector<int> result = solution(prices);
    for (int r : result)
    {
        cout << r << ",";
    }
    cout << endl;
    return 0;
}