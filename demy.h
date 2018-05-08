#ifndef DEMY_H
#define DEMY_H

#ifdef __cplusplus
extern "C" {
#endif

struct demy_timeline;
struct demy_track;
struct demy_node;
struct demy_node_iterator;

enum interp_t
{
    DEMY_E_INTERP_NONE = 0,
    DEMY_E_INTERP_LINEAR = 1
};

demy_timeline* demy_tl_new();
void demy_tl_free(demy_timeline* tl);
demy_track* demy_tl_track_get(demy_timeline* tl, const char *name);
bool demy_tl_track_del(demy_timeline *tl, const char *name);

bool demy_tr_add_node(demy_track *track, unsigned int time, double value, interp_t interp);
bool demy_tr_del_node(demy_track *track, unsigned int time);
const demy_node* demy_tr_get_node(const demy_track *track, unsigned int time);

demy_node_iterator* demy_tr_iter_begin(const demy_track *track);
demy_node_iterator* demy_tr_iter_end(const demy_track *track);
void demy_tr_iter_free(demy_node_iterator *iter);
void demy_tr_iter_next(demy_node_iterator **ptr_to_iter);
const demy_node* demy_tr_iter_get(const demy_node_iterator *iter);
bool demy_tr_iter_are_eq(const demy_node_iterator *a, const demy_node_iterator *b);

bool demy_node_update_at(demy_track *track, unsigned int time, const demy_node *node);
demy_node* demy_node_clone(const demy_node *node);
demy_node* demy_node_new(unsigned int time, double value, interp_t interp);
void demy_node_free(demy_node *node);

bool demy_tl_save(demy_timeline *tl, const char* path);
demy_timeline* demy_tl_load(const char* path);

void demy_node_set_interp(demy_node *node, interp_t interp);
interp_t demy_node_get_interp(demy_node *node);
void demy_node_set_value(demy_node *node, double value);
double demy_node_get_value(demy_node *node);
void demy_node_set_time(demy_node *node, unsigned int time);
unsigned int demy_node_get_time(demy_node *node);

#ifdef __cplusplus
}
#endif

#endif // DEMY_H
