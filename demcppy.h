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
                        // TODO : Iter
            }


            Track(demy_track *tr);
            ~Track() = default;

            demy_track* GetCPtr();

            bool AddNode(unsigned int time, double value, InterpType interp);
            bool DeleteNode(unsigned int time);
            bool GetNode(unsigned int time, Node &outNode);
            
    };

    class Node 
    {
        const demy_node *_c_node;
        bool _is_owned;

        public:
            Node();
            Node(const Node &oth);
            Node(const demy_node *node, bool is_owned);
            ~Node();

            void SetInterpolation(InterpType interp);
            InterpType GetInterpolation();

            void SetTime(unsigned int time);
            unsigned int GetTime();

            void SetValue(double value);
            double GetValue();

            demy_node* GetCPtr();
    };
}

#endif // DEMCPPY_H

#ifdef DEMCPPY_IMPLEMENTATION

Demy::Node Demy::Node(unsigned int time, double value, InterpType interp)
    : _c_node(demy_node_new(time, value, interp)),
    _is_owned(true)
{
}

Demy::Node Demy::Node(const Node &oth)
    : _c_node(demy_node_clone(oth.GetCPtr()),
    _is_owned(true)
{

}

Demy::Node Demy::Node(const demy_node *node, bool is_owned)
    : _c_node(node),
    _is_owned(is_owned)
{
}

~Demy::Node Demy::Node()
{
    if(_is_owned)
    {
        demy_node_free(_c_node);
    }
}

void Demo::Node::SetInterpolation(InterpType interp)
{
    demy_node_set_interp(_c_node, interp);
}

InterpType Demo::Node::GetInterpolation()
{
    return demy_node_get_interp(_c_node);
}

void Demo::Node::SetTime(unsigned int time)
{
    demy_node_set_time(_c_node, time);
}

unsigned int Demo::Node::GetTime()
{
    return demy_node_get_time(_c_node);
}

void Demo::Node::SetValue(double value)
{
    demy_node_set_value(_c_node, value);
}

double Demo::Node::GetValue()
{
    return demy_node_get_value(_c_node);
}

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
    return Demy::Track(demy_tr_track_get(_c_tl, name.c_str());
}

bool Demy::Timeline::DeleteTrack(const std::string &name)
{
    return demy_tr_track_del(_c_tl, name.c_str());
}

Demy::Track Demy::Track(demy_track *track)
    _c_tr(track)
{
}

demy_track* Demy::Track::GetCPtr()
{
    return _c_tr;
}


bool Demy::Track::AddNode(unsigned int time, double value, InterpType interp)
{
    return demy_tr_add_node(_c_tr, time, value, interp);
}

bool Demy::Track::DeleteNode(unsigned int time)
{
    return demy_try_del_node(_c_tr, time);
}

bool Demy::Track::GetNode(unsigned int time, const Node &outNode)
{
    const demy_node *node = demy_tr_get_node(_c_tr, time);
    if(node)
    {
        outNode = Demy::Node(node);
        return true;
    }
    return false;

}

#endif
