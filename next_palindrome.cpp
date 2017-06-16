#include <iostream>
#include <cmath>
#include <deque>
#include <string>
#include <cassert>


typedef struct{
    long long       origin_i;
    long long       origin_j;
    long long       i;
    long long       j;
    bool            is_even;
} ContainerInfo;


long long convertDequeToInt(std::deque<int>& deque){
    long long number = 0;
    for (int n: deque){
        number = number * 10 + n;
    }
    return number;
}

void convertIntToDeque(long long value, std::deque<int>& deque){
    int digit;
    while(value > 0){
        digit = (int)value % 10;
        value /= 10;
        deque.push_front(digit);
    }
    if(deque.empty()) deque.push_back(0);
}

void copyLeftHalfToRightHalf(std::deque<int> &deque, long long lindex){
    long length = deque.size();
    long rindex = length - 1 - lindex;
    while(lindex >= 0){
        deque[rindex] = deque[lindex];
        lindex--;
        rindex++;
    }
}

//resolve carry and copy left to right side after if required
void checkForCarry(std::deque<int>& deque, long long index){
    long long lindex = index;
    while(deque[lindex] > 9 && lindex > 0){
        deque[lindex--] = 0;
        deque[lindex]++;
    }
    if (deque[lindex] > 9){
        deque[lindex] = 0;
        deque.push_front(1);
    }
    copyLeftHalfToRightHalf(deque, index);
}
    

//initially set center indices to center
void initContainerInfo(std::deque<int>& container, ContainerInfo& data){
    long long half = ceil((double(container.size()))/2);
    data.origin_i = data.i = half;
    data.origin_j = data.j = half - 1;
    data.is_even = (container.size() % 2) == 0;
    if (!data.is_even){
        data.j--;
        data.origin_j = data.origin_i = data.i - 1;
    }
}

void findNextPalindrome(std::deque<int>& digit_deque){
    if (digit_deque.size() == 1){
        (digit_deque[0] < 9) ? (digit_deque[0] += 1) : (digit_deque[0] = 11);
        return;
    }
    ContainerInfo info;
    initContainerInfo(digit_deque, info);

    while(info.j >= 0){
        // case: left index greater than right one -> just mirror left site to the right, starting from this index
        if (digit_deque[info.j] > digit_deque[info.i]){
            copyLeftHalfToRightHalf(digit_deque, info.j);
            return;
        }
        //case: right index greated than left one -> increment central digit(s) and check for carry. 
        else if (digit_deque[info.j] < digit_deque[info.i]){
            digit_deque[info.origin_j]++;
            if(info.is_even){
                digit_deque[info.origin_i]++;
            }
            checkForCarry(digit_deque, info.origin_j);
            return;
        }
        //case: both indices hold the same value -> let's see the next, by moving the to indices one step further in opposite direction so [<-y | i->]  
        else{
            info.i++;
            info.j--;
        }
    }
    //at this point we know we already have a palindrome -> increment center and check for carry!
    digit_deque[info.origin_j]++;
    if(info.is_even){
        digit_deque[info.origin_i]++;
    }
    checkForCarry(digit_deque, info.origin_j);
}

void printDequeAsNumber(std::deque<int>& deque){
    for(int num: deque)
    {
        std::cout << num;
    }
    std::cout << std::endl;
}

int main() {
    char c;
    std::string buf;
    while(std::getline(std::cin, buf)){
        std::deque<int> digit_deque;
        for(int x = 0; x < buf.size(); ++x){
            c = buf[x];
            digit_deque.push_back((int)(c - '0'));
        }
        findNextPalindrome(digit_deque);
        printDequeAsNumber(digit_deque);
    }
    return 0;
}