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
            Timeline();
            Timeline(demy_timeline *tl) : _c_tl(tl) { }
            static Timeline* Load(const std::string& filepath);

            ~Timeline();

            demy_timeline* GetCPtr() const;

            Track GetTrack(const std::string &name);
            bool DeleteTrack(const std::string &name);

            void Save(const std::string& filepath) const;
    };

    class Track
    {
        demy_track *_c_tr;

        public:

            class iterator 
            {
                demy_node_iterator *_c_iter;
                public:
                    using difference_type = std:ptrdiff_t;
                    using value_type = Node;
                    using pointer = const *Node;
                    using reference = const &Node;
                    using iterator_category = std::forward_iterator_tag;

                    iterator(demy_node_iterator *iter);
                    ~iterator();

                    iterator& operator++();
                    bool operator==(const iterator& other) const;
                    reference operator*() const;
            }

            Track(demy_track *tr);
            ~Track() = default;

            demy_track* GetCPtr() const;

            bool AddNode(unsigned int time, double value, InterpType interp);
            bool DeleteNode(unsigned int time);
            bool GetNode(unsigned int time, Node &outNode) const;

            iterator begin() const
            { return iterator(demy_tr_iter_begin(_c_tr); }

            iterator end() const
            { return iterator(demy_tr_iter_end(_c_tr); }
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
            InterpType GetInterpolation() const;

            void SetTime(unsigned int time);
            unsigned int GetTime() const;

            void SetValue(double value);
            double GetValue() const;

            demy_node* GetCPtr() const;
    };
}

#endif // DEMCPPY_H

#ifdef DEMCPPY_IMPLEMENTATION

DemyTrack::iterator Demy::Track::iterator(demy_node_iterator *iter) 
    : _c_iter(iter) 
{
}

~Demy::Track::iterator Demy::Track::iterator() 
{ 
    demy_tr_iter_free(_c_iter); 
}

Demy::Track::iterator& Demy::Track::iterator::operator++() 
{ 
    demy_tr_iter_next(&_c_iter); 
    return *this; 
}

bool Demy::Track::iterator::operator==(const Demy::Track::iterator& other) const ]
{ 
    return demy_tr_iter_are_eq(this, &other); 
}

Demy::Track::iterator::reference Demy::Track::iterator::operator*() const 
{ 
    return demy_tr_iter_get(_c_iter); 
}

Demy::Timeline* Demy::Timeline::Load(const std::string& filepath)
{
    demy_timeline *tl = demy_tl_load(filepath.c_str());
    return tl;
}

bool Demy::Timeline::Save(const std::string& filepath) const
{
}

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

InterpType Demo::Node::GetInterpolation() const
{
    return demy_node_get_interp(_c_node);
}

void Demo::Node::SetTime(unsigned int time)
{
    demy_node_set_time(_c_node, time);
}

unsigned int Demo::Node::GetTime() const
{
    return demy_node_get_time(_c_node);
}

void Demo::Node::SetValue(double value)
{
    demy_node_set_value(_c_node, value);
}

double Demo::Node::GetValue() const
{
    return demy_node_get_value(_c_node);
}

Demy::Timeline Demy::Timeline()
    _c_tl(demy_tl_new())
{
}

~Demy::Timeline Demy::Timeline()
{
    if(_c_tl)
    {
        demy_tl_free(_c_tl);
        _c_tl = 0;
    }
}

Demy::Timeline::GetCPtr() const
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

demy_track* Demy::Track::GetCPtr() const
{
    return _c_tr;
}

demy_node* Demy::Node::GetCPtr() const
{
    return _c_node;
}

bool Demy::Track::AddNode(unsigned int time, double value, InterpType interp)
{
    return demy_tr_add_node(_c_tr, time, value, interp);
}

bool Demy::Track::DeleteNode(unsigned int time)
{
    return demy_try_del_node(_c_tr, time);
}

bool Demy::Track::GetNode(unsigned int time, const Node &outNode) const
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
