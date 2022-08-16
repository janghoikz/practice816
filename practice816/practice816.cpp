#include <iostream>

using namespace std;

// : 동적 할당

//메모리 구조복습
// - 실행할 코드가 저장되는 영역 -> 코드영역
// - 전역(global)/정적(static)변수 -> 데이터 영역
// - 지역변수 /매개변수 ->스택 영역
// - 동적할당 -> 힙 영역

//지금까지 데이터 영역/ 스택영역 이용해서
// 이런 저런 프로그램을 잘 만들어 왔다!
// 굳이 새로운 영역이 필요할까?

// 실제상황)가정
// - mmorpg 동접 1~5만명, 몬스터 1~500만마리

// - 스택 영역
// 함수가 끝나면 같이 정리되는 불안정한 메모리
// 잠시 함수에 매개변수 넘긴다거나, 하는 용도로는 ok
// - 메모리영역
// 프로그램이 실행되는 도중에는 '무조건' 사용되는 공간

// 희망사항)
// - 필요할때만 사용하고, 필요없으면 반납할수 있는!
// - 그러면서도 (스택과는 다르게) 우리가 생성/소멸 시점을 관리할 수있는
// - 힙 영역
// 동적할당과 연관된 함수/연산자 : malloc/free, new/delete, new[]/delete[]

//malloc
// - 할당할 메모리 크기를 건내준다
// - 메모리 할당 후 시작주소를 가리키는 포인터를 반환해준다(메모리 부족 n    ull)

// free
// - malloc (혹은 기타 calloc, realloc 등의 사촌)을 통해 할당된 영역을 해제
// - 힙 관리자가 할당/미할당 여뷰를 구분해서 관리

// new / delete
// - c++에서 추가됨
// - malloc/free는 함수 new/delete는 연산자

// new[] / delete[]
// - new / delete 비해 좋긴한데 - 배열과 같이 n개 데이터를 같이 할당하려면?

// malloc/free vs new/delete
// - 사용편의성 -> new/delete 승!
// - 타입에 상관없이 특정한 크기의 메모리 영역을 할당 받으려면? -> malloc/free 승!

// 그런데 둘의 가장 가장 근본적인 중요한 차이는 따로있음!
// new/delete는 (생성타입이 클래스일 경우) 생성자/소멸자를 호출해준다!!

class Monster
{
public:
    Monster()
    {
        cout << "Monster()" << endl;
    }
    ~Monster()
    {
        cout << "~Monster()" << endl;
    }
public:
    int _hp;
    int _x;
    int _y;
};

int main()
{
    //유저영역 게임이나 각종 프로그램
    //-------------------------
    //커널영역(windows 등의 핵심 코드)

    // 유저영역) 운영체제에서 제공하는 api호출
    // 커널영역) 메모리 할당해서 건내줌
    // 유저영역) 할당받은걸 사용

    // [                ]
    // c++ 에서는 기본적은 crt(C런타임 라이브러리)의 [힙 관리자]를 통해 힙 영역 사용
    // 단, 정말 원한다면 우리가 직접api를 통해 힙을 생성하고 관리할 수도 있음(MMORPG 서버 메모리 풀링)

    
#ifdef _WIN64
    typedef unsigned __int64 size_t;
#else
    typedef unsigned int     size_t;
#endif
    //실시간으로 할당할수있는 1000바이트 받는다
    // void* ?? 무엇인가
    // *가 있으니까 포인터는 포인터 (주소를 담는 바구니) => ok
    // 타고가면  void 아무것도 없다? => no
    // 타고가면 void 뭐가있는지 모르겠으니까 너가 적당히 변환해서 사용해라 => ok
    void* pointer = malloc(12);

    Monster* m1 = (Monster*)pointer;
    m1->_hp = 100;
    m1->_x = 1;
    m1->_y = 2;

    // Heap Overflow
    // - 유효한 힙 범위를 초과를 사용하는 문제
    
    free(pointer);
    // free를 하지않으면 메모리 누수
    
    // Double Free
    // - 이거는 대부분 크래시만 나고 끝난다

    // Use-After-Free
    // free로 지우고나서 또 사용하는경우
    // - 프로그래머 입장 : OMG 망했다!
    // - 해커입장 : 심봤다!

    //free하고 나서도 안쓰게 메모리를 밀어주는것도 좋다
    //pointer = nullptr;
    //m1 = nullptr;

    //한마리만 만드는
    //가장 자주 사용되는 방식
    Monster* m2 = new Monster;
    m2->_hp = 200;
    m2->_x = 3;
    m2->_y = 4;
    delete m2;

    //여러마리 동시에 만들기
    Monster* m3 = new Monster[5];
    m3->_hp = 200;
    m3->_x = 3;
    m3->_y = 4;

    Monster* m4 = (m3 + 1);
    m4->_hp = 200;
    m4->_x = 3;
    m4->_y = 4;

    delete[] m3;
}