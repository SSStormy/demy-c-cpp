#ifndef DEMCPPY_H
#define DEMCPPY_H

#include <demy.h> // c-bindings

namespace Demy
{
    enum InterpType
    {
        None = DEMY_E_INTERP_NONE,
        Linear = DEMY_E_INTERP_LINEAR
    };

    class Timeline 
    {
        demy_timeline *_c_tl;

        public:
            DemyTimeline();
            ~DemyTimeline();

            demy_timeline* GetCPtr();

            Track GetTrack(const std::string &name);
            bool DeleteTrack(const std::string &name);
    };

    class Track
    {
        demy_track *_c_tr;

        public:

            class iterator 
            {
                demy_node_iterator *_c_iter;
                public:
                    iterator(demy_node_iterator *iter) : _c_iter(iter) {}
                    iterator& operator++() { demy_tr_iter_next(&_c_iter); return *this; }
                    bool operator==(iterator other) const { return other.

            }


            Track(demy_track *tr);
            ~Track();

            demy_track* GetCPtr();

            bool AddNode(unsigned int time, double value, InterpType interp);
            bool DeleteNode(unsigned int time);
            bool GetNode(unsigned int time, Node &outNode);
            
    };

    class Node 
    {
        const demy_node *_c_node;

        public:
            Node(const demy_node *node);
            ~Node();

            void SetInterpolation();
            void GetInterpolation();

            void SetTime();
            void GetTime();

            void SetValue();
            void GetValue();

            demy_node* GetCPtr();
    };
}

#endif // DEMCPPY_H

#ifdef DEMCPPY_IMPLEMENTATION

Demy::Timeline Demy::Timeline()
    _c_tl(0)
{
    _c_tl = demy_tl_new();
}

~Demy::Timeline Demy::Timeline()
{
    if(_c_tl)
    {
        demy_tl_free(_c_tl);
        _c_tl = 0;
    }
}

Demy::Timeline::GetCPtr()
{
    return _c_tl;
}

Demy::Track Demy::Timeline::GetTrack(const std::string &name)
{
}

bool Demy::Timeline::DeleteTrack(const std::string &name)
{
}

#endif
