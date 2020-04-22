#include "inc.h"
//struct Uses23GB
//{
//unsigned char m_buffer[11'184'800]{0};
//} s_hurtsMem;

struct KillsPC
{
    unsigned char m_buffer[22'369'616]{ 0 };
} s_killsPC;

struct a {};
struct b {
    explicit b(a* const& child) {}
};
struct c : a {
    c(std::initializer_list<b*>&& children) {}
};

void test()
{
    //b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new c({
    //new b(new a())
    //}))
    //}))
    //}))
    //}))
    //}))
    //}))
    //}))
    //}))
    //    }));
}