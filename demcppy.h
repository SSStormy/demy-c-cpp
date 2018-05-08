#ifndef DEMCPPY_H
#define DEMCPPY_H

#include <demy.h> // c-bindings

namespace Demy
{
    class Track;
    class Node;

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

            Demy::Track GetTrack(const std::string &name);
            bool DeleteTrack(const std::string &name);

            bool Save(const std::string& filepath) const;
    };

    class Track
    {
        demy_track *_c_tr;

        public:

            class iterator 
            {
                demy_node_iterator *_c_iter;

                public:
                    using difference_type = std::ptrdiff_t;
                    using value_type = Node;
                    using pointer = const Node*;
                    using reference = const Node&;
                    using iterator_category = std::forward_iterator_tag;

                    iterator(demy_node_iterator *iter) : _c_iter(iter) { }
                    ~iterator();

                    iterator& operator++();
                    bool operator==(const iterator& other) const;
                    bool operator!=(const iterator& other) const;
                    value_type operator*() const;

                    demy_node_iterator* GetCPtr() const;
            };

            Track(demy_track *tr);
            ~Track() = default;

            demy_track* GetCPtr() const;

            bool AddNode(unsigned int time, double value, InterpType interp);
            bool DeleteNode(unsigned int time);
            bool GetNode(unsigned int time, Demy::Node *const outNode) const;

            iterator begin() const
            { return iterator(demy_tr_iter_begin(_c_tr)); }

            iterator end() const
            { return iterator(demy_tr_iter_end(_c_tr)); }
    };

    class Node 
    {
        demy_node *_c_node;
        bool _is_owned;

        public:
            Node(unsigned int time, double value, InterpType interp);
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

#ifdef DEMCPPY_IMPLEMENTATION

    Track::iterator::~iterator() 
    { 
        demy_tr_iter_free(_c_iter); 
    }

    demy_node_iterator* Track::iterator::GetCPtr() const
    {
        return _c_iter;
    }

    Track::iterator& Track::iterator::operator++() 
    { 
        demy_tr_iter_next(&_c_iter); 
        return *this; 
    }

    bool Track::iterator::operator!=(const Track::iterator& other) const
    {
        return !(*this == other);
    }

    bool Track::iterator::operator==(const Track::iterator& other) const
    { 
        return demy_tr_iter_are_eq(GetCPtr(), other.GetCPtr()); 
    }

    Track::iterator::value_type Track::iterator::operator*() const 
    { 
        return Node(demy_tr_iter_get(_c_iter), false);
    }

    Timeline* Timeline::Load(const std::string& filepath)
    {
        demy_timeline *tl = demy_tl_load(filepath.c_str());
        if(tl)
            return new Timeline(tl);
        return nullptr;
    }

    bool Timeline::Save(const std::string& filepath) const
    {
        return demy_tl_save(_c_tl, filepath.c_str());
    }

    Node::Node(unsigned int time, double value, InterpType interp)
        : _c_node(demy_node_new(time, value, (interp_t)interp)),
        _is_owned(true)
    {
    }

    Node::Node(const Node &oth)
        : _c_node(demy_node_clone(oth.GetCPtr())),
        _is_owned(true)
    {

    }

    Node::Node(const demy_node *node, bool is_owned)
        : _c_node(const_cast<demy_node*>(node)),
        _is_owned(is_owned)
    {
    }

    Node::~Node()
    {
        if(_is_owned)
        {
            demy_node_free(_c_node);
        }
    }

    void Node::SetInterpolation(InterpType interp)
    {
        demy_node_set_interp(_c_node, (interp_t)interp);
    }

    InterpType Node::GetInterpolation() const
    {
        return (InterpType)demy_node_get_interp(_c_node);
    }

    void Node::SetTime(unsigned int time)
    {
        demy_node_set_time(_c_node, time);
    }

    unsigned int Node::GetTime() const
    {
        return demy_node_get_time(_c_node);
    }

    void Node::SetValue(double value)
    {
        demy_node_set_value(_c_node, value);
    }

    double Node::GetValue() const
    {
        return demy_node_get_value(_c_node);
    }

    Timeline::Timeline()
        : _c_tl(demy_tl_new())
    {
    }

    Timeline::~Timeline()
    {
        if(_c_tl)
        {
            demy_tl_free(_c_tl);
            _c_tl = 0;
        }
    }

    demy_timeline* Timeline::GetCPtr() const
    {
        return _c_tl;
    }

    Track Timeline::GetTrack(const std::string &name)
    {
        return Track(demy_tl_track_get(_c_tl, name.c_str()));
    }

    bool Timeline::DeleteTrack(const std::string &name)
    {
        return demy_tl_track_del(_c_tl, name.c_str());
    }

    Track::Track(demy_track *track)
        : _c_tr(track)
    {
    }

    demy_track* Track::GetCPtr() const
    {
        return _c_tr;
    }

    demy_node* Node::GetCPtr() const
    {
        return _c_node;
    }

    bool Track::AddNode(unsigned int time, double value, InterpType interp)
    {
        return demy_tr_add_node(_c_tr, time, value, (interp_t)interp);
    }

    bool Track::DeleteNode(unsigned int time)
    {
        return demy_tr_del_node(_c_tr, time);
    }

    bool Track::GetNode(unsigned int time, Node *const outNode) const
    {
        const demy_node *node = demy_tr_get_node(_c_tr, time);
        if(node)
        {
            if(outNode)
                *outNode = Node(node, false);

            return true;
        }
        return false;

    }

#endif

};

#endif // DEMCPPY_H
