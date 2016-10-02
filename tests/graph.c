#include "graph.h"
#include "graph/graph.h"
#include "lib/set.h"

#include <stdio.h>

typedef struct {
    /* vector of sets of neighbours */
    vector_t neighbours;

    list_t queue;
} bfs_checker_t;

typedef struct {
    /* vector of sets of neighbours */
    vector_t neighbours;
    /* stack of vertices */
    list_t stack;
} dfs_checker_t;

graph_t *G = NULL;
bool DIRECTED;

void setup(void) {
    graph_edge_count_t i;
    graph_vertex_idx_t from, to;
    graph_edge_idx_t __attribute__((unused)) e;
    void *vertices_data[10] = {
        (void *)0, (void *)1, (void *)2, (void *)3, (void *)4,
        (void *)5, (void *)6, (void *)7, (void *)8, (void *)9
    };

    graph_init(G, 10, vertices_data, DIRECTED);

    for (i = 0, from = 0, to = 1; i < 4; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 1, to = 2; i < 3; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 2, to = 1; i < 2; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 2, to = 4; i < 8; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 4, to = 3; i < 9; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 3, to = 5; i < 5; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 5, to = 6; i < 7; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 6, to = 7; i < 10; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 7, to = 0; i < 13; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 7, to = 8; i < 11; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));

    for (i = 0, from = 9, to = 8; i < 12; ++i)
        e = graph_add_update_edge(G, from, to, (void *) (i + 1));
}

void teardown(void) {
    graph_deinit(G, NULL, NULL);
    G = NULL;
}

void setup_algorithms(graph_t *g) {
    void *vdata[10];
    graph_init(g, 10, vdata, !GRAPH_DIRECTED);

    graph_add_update_edge(g, 0, 3, (void *)1);
    graph_add_update_edge(g, 0, 9, (void *)2);

    graph_add_update_edge(g, 1, 2, (void *)3);
    graph_add_update_edge(g, 1, 3, (void *)4);

    graph_add_update_edge(g, 2, 8, (void *)5);
    graph_add_update_edge(g, 2, 9, (void *)6);

    graph_add_update_edge(g, 3, 4, (void *)7);
    graph_add_update_edge(g, 3, 6, (void *)8);
    graph_add_update_edge(g, 3, 9, (void *)9);

    graph_add_update_edge(g, 4, 5, (void *)10);

    graph_add_update_edge(g, 5, 6, (void *)11);
    graph_add_update_edge(g, 5, 7, (void *)12);

    graph_add_update_edge(g, 7, 8, (void *)13);

    graph_add_update_edge(g, 8, 9, (void *)14);

    ck_assert_int_eq(g->edges_number, 14);
}

void teardown_algorithms(graph_t *g) {
    graph_deinit(g, NULL, NULL);
}

START_TEST(test_graph_directed_ok) {
    graph_t g;

    G = &g;
    DIRECTED = GRAPH_DIRECTED;

    setup();

    ck_assert_int_eq(graph_test_edge(G, 0, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 1).data, 4);
    ck_assert_int_eq(graph_test_edge(G, 0, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 1, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 2).data, 3);
    ck_assert_int_eq(graph_test_edge(G, 1, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 2, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 1).data, 2);
    ck_assert_int_eq(graph_test_edge(G, 2, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 4).data, 8);
    ck_assert_int_eq(graph_test_edge(G, 2, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 3, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 5).data, 5);
    ck_assert_int_eq(graph_test_edge(G, 3, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 4, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 3).data, 9);
    ck_assert_int_eq(graph_test_edge(G, 4, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 5, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 6).data, 7);
    ck_assert_int_eq(graph_test_edge(G, 5, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 6, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 7).data, 10);
    ck_assert_int_eq(graph_test_edge(G, 6, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 7, 0).data, 13);
    ck_assert_int_eq(graph_test_edge(G, 7, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 8).data, 11);
    ck_assert_int_eq(graph_test_edge(G, 7, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 8, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 9, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 8).data, 12);
    ck_assert_int_eq(graph_test_edge(G, 9, 9).found, false);

    teardown();
}
END_TEST

START_TEST(test_graph_undirected_ok) {
    graph_t g;

    G = &g;
    DIRECTED = !GRAPH_DIRECTED;

    setup();

    ck_assert_int_eq(graph_test_edge(G, 0, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 1).data, 4);
    ck_assert_int_eq(graph_test_edge(G, 0, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 7).data, 13);
    ck_assert_int_eq(graph_test_edge(G, 0, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 0, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 1, 0).data, 4);
    ck_assert_int_eq(graph_test_edge(G, 1, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 2).data, 2);
    ck_assert_int_eq(graph_test_edge(G, 1, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 1, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 2, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 1).data, 2);
    ck_assert_int_eq(graph_test_edge(G, 2, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 4).data, 8);
    ck_assert_int_eq(graph_test_edge(G, 2, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 2, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 3, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 4).data, 9);
    ck_assert_int_eq(graph_test_edge(G, 3, 5).data, 5);
    ck_assert_int_eq(graph_test_edge(G, 3, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 3, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 4, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 2).data, 8);
    ck_assert_int_eq(graph_test_edge(G, 4, 3).data, 9);
    ck_assert_int_eq(graph_test_edge(G, 4, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 4, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 5, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 3).data, 5);
    ck_assert_int_eq(graph_test_edge(G, 5, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 6).data, 7);
    ck_assert_int_eq(graph_test_edge(G, 5, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 5, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 6, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 5).data, 7);
    ck_assert_int_eq(graph_test_edge(G, 6, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 7).data, 10);
    ck_assert_int_eq(graph_test_edge(G, 6, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 6, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 7, 0).data, 13);
    ck_assert_int_eq(graph_test_edge(G, 7, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 6).data, 10);
    ck_assert_int_eq(graph_test_edge(G, 7, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 7, 8).data, 11);
    ck_assert_int_eq(graph_test_edge(G, 7, 9).found, false);

    ck_assert_int_eq(graph_test_edge(G, 8, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 7).data, 11);
    ck_assert_int_eq(graph_test_edge(G, 8, 8).found, false);
    ck_assert_int_eq(graph_test_edge(G, 8, 9).data, 12);

    ck_assert_int_eq(graph_test_edge(G, 9, 0).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 1).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 2).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 3).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 4).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 5).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 6).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 7).found, false);
    ck_assert_int_eq(graph_test_edge(G, 9, 8).data, 12);
    ck_assert_int_eq(graph_test_edge(G, 9, 9).found, false);

    teardown();
}
END_TEST

static
bool check_bfs(const graph_t const *g, graph_vertex_idx_t v,
               bfs_checker_t *checker) {
    graph_vertex_idx_t idx;

    fprintf(
        stderr,
        "Enqueue %llu\n",
        (long long unsigned int)v
    );
    *(graph_vertex_idx_t *)(list_append(&checker->queue)->data) = v;

    if (*(graph_vertex_idx_t *)(list_begin(&checker->queue)->data) != v) {
        ck_assert_int_gt(
            set_count(
                (set_t *)
                vector_get(&checker->neighbours,
                           *(graph_vertex_idx_t *)
                           (list_begin(&checker->queue)->data)),
                      v),
                      0
        );

        fprintf(
            stderr,
            "  Neighbour %llu of %llu (%llu)\n",
                (long long unsigned int)v,
                (long long unsigned int)(*(graph_vertex_idx_t *)
                                         (list_begin(&checker->queue)->data)),
                (long long unsigned int)set_count(
                    (set_t *)vector_get(&checker->neighbours,
                                        *(graph_vertex_idx_t *)
                                        (list_begin(&checker->queue)->data)),
                    v
                )
        );

        if (1 == set_size((set_t *)vector_get(&checker->neighbours,
                          *(graph_vertex_idx_t *)
                          (list_begin(&checker->queue)->data)))) {
            fprintf(
                stderr,
                "   Dequeue %llu\n",
                (long long unsigned int)
                *(graph_vertex_idx_t *)(list_begin(&checker->queue)->data)
            );

            list_remove_and_advance(&checker->queue,
                                    list_begin(&checker->queue));

        }   /* if (1 == set_size((set_t *)vector_get(&checker->neighbours, */
    }   /* if (*(graph_vertex_idx_t *)(list_begin(&checker->queue)->data) != v) */

    for (idx = 0; idx < v; ++idx)
        set_remove((set_t *)vector_get(&checker->neighbours, idx), v);

    for (; idx < g->vertices_number; ++idx)
        set_remove((set_t *)vector_get(&checker->neighbours, idx), v);

    while (list_begin(&checker->queue) &&
           0 == set_size((set_t *)vector_get(&checker->neighbours,
                         *(graph_vertex_idx_t *)
                         (list_begin(&checker->queue)->data)))) {
        fprintf(
            stderr,
            "   Dequeue %llu\n",
            (long long unsigned int)
            *(graph_vertex_idx_t *)(list_begin(&checker->queue)->data)
        );

        list_remove_and_advance(&checker->queue, list_begin(&checker->queue));
    }   /* while (list_begin(&checker->queue) && */

    return true;
}

START_TEST(test_graph_bfs_ok) {
    static const graph_vertex_idx_t INITIAL = 0;

    graph_t g;
    bfs_checker_t bfs_checker;
    graph_vertex_idx_t v;
    list_t *adj_list;
    list_element_t *adj_v;

    setup_algorithms(&g);

    vector_init(&bfs_checker.neighbours, sizeof(set_t), g.vertices_number);
    for (v = 0; v < g.vertices_number; ++v) {
        set_init((set_t *)vector_get(&bfs_checker.neighbours, v));

        adj_list = vector_get(&g.adjacency_list, v);
        for (adj_v = list_begin(adj_list); adj_v;
             adj_v = list_next(adj_list, adj_v))
            set_add_single(
                (set_t *)vector_get(&bfs_checker.neighbours, v),
                *(graph_vertex_idx_t *)(adj_v->data)
            );
    }

    list_init(&bfs_checker.queue, true, sizeof(graph_vertex_idx_t));

    graph_bfs(&g, INITIAL, (graph_vertex_runner_t)check_bfs, &bfs_checker);

    for (v = 0; v < g.vertices_number; ++v)
        ck_assert_int_eq(
            set_size((set_t *)vector_get(&bfs_checker.neighbours, v)), 0);

    for (v = 0; v < g.vertices_number; ++v)
        set_purge((set_t *)vector_get(&bfs_checker.neighbours, v));

    vector_deinit(&bfs_checker.neighbours);
    list_purge(&bfs_checker.queue);

    teardown_algorithms(&g);
}
END_TEST

START_TEST(test_graph_dfs_ok) {
    graph_t g;
    setup_algorithms(&g);
    ck_assert_int_ne(0,0);
    teardown_algorithms(&g);
}
END_TEST

START_TEST(test_graph_random_path_ok) {
    graph_t g;
    setup_algorithms(&g);
    ck_assert_int_ne(0,0);
    teardown_algorithms(&g);
}
END_TEST

START_TEST(test_graph_untie_path_ok) {
    graph_t g;
    list_t path;
    list_element_t *le_path;

    setup_algorithms(&g);

    list_init(&path, true, sizeof(graph_vertex_idx_t));
    *(graph_vertex_idx_t *)list_append(&path)->data = 0;
    *(graph_vertex_idx_t *)list_append(&path)->data = 3;
    *(graph_vertex_idx_t *)list_append(&path)->data = 6;
    *(graph_vertex_idx_t *)list_append(&path)->data = 5;
    *(graph_vertex_idx_t *)list_append(&path)->data = 4;
    *(graph_vertex_idx_t *)list_append(&path)->data = 3;
    *(graph_vertex_idx_t *)list_append(&path)->data = 9;
    *(graph_vertex_idx_t *)list_append(&path)->data = 8;
    *(graph_vertex_idx_t *)list_append(&path)->data = 2;
    *(graph_vertex_idx_t *)list_append(&path)->data = 9;

    graph_untie_path(&g, &path);

    ck_assert_int_eq(list_size(&path), 3);

    le_path = list_begin(&path);
    ck_assert_int_eq(*(graph_vertex_idx_t *)le_path->data, 0);

    le_path = list_next(&path, le_path);
    ck_assert_int_eq(*(graph_vertex_idx_t *)le_path->data, 3);

    le_path = list_next(&path, le_path);
    ck_assert_int_eq(*(graph_vertex_idx_t *)le_path->data, 9);

    list_purge(&path);

    teardown_algorithms(&g);
}
END_TEST

Suite *graph_suite(void) {
    Suite *s = suite_create("graph");
    TCase *tc = tcase_create("directed multi");

    tcase_add_test(tc, test_graph_directed_ok);

    suite_add_tcase(s, tc);

    tc = tcase_create("undirected multi");

    tcase_add_test(tc, test_graph_undirected_ok);

    suite_add_tcase(s, tc);

    tc = tcase_create("algorithms");

    tcase_add_test(tc, test_graph_bfs_ok);
    tcase_add_test(tc, test_graph_dfs_ok);
    tcase_add_test(tc, test_graph_random_path_ok);
    tcase_add_test(tc, test_graph_untie_path_ok);

    suite_add_tcase(s, tc);

    return s;
}
