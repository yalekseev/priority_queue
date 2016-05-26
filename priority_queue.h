#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename Cmp = std::less<T>>
class priority_queue {
public:
    T& top() {
        return m_heap[0];
    }

    const T& top() const {
        return m_heap[0];
    }

    void pop() {
        int i = m_queue_size - 1;
        std::swap(m_heap[0], m_heap[i]);
        --m_queue_size;
        sift_down(0);
    }

    void push(const T &t) {
        if (m_queue_size == m_heap.size()) {
            m_heap.push_back(t);
            ++m_queue_size;
        } else {
            m_heap[m_queue_size] = t;
            ++m_queue_size;
        }

        sift_up(m_queue_size - 1);
    }

    size_t size() const {
        return m_queue_size;
    }

    bool empty() const {
        return m_queue_size == 0;
    }

private:
    void sift_up(int i) {
        int p = parent(i);

        while (p >= 0 && m_cmp(m_heap[p], m_heap[i])) {
            std::swap(m_heap[p], m_heap[i]);
            sift_up(p);
        }
    }

    void sift_down(int i) {
        int left = left_child(i);
        int right = right_child(i);

        if (left < m_queue_size && right < m_queue_size) {
            int max = left;
            if (m_cmp(m_heap[max], m_heap[right])) {
                max = right;
            }

            if (m_cmp(m_heap[i], m_heap[max])) {
                std::swap(m_heap[i], m_heap[max]);
                sift_down(max);
            }
        } else if (left < m_queue_size && m_cmp(m_heap[i], m_heap[left])) {
            std::swap(m_heap[i], m_heap[left]);
            sift_down(left);
        } else if (right < m_queue_size && m_cmp(m_heap[i], m_heap[right])) {
            std::swap(m_heap[i], m_heap[right]);
            sift_down(right);
        }
    }

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left_child(int i) {
        return 2 * i + 1;
    }

    int right_child(int i) {
        return 2 * i + 2;
    }

private:
    Cmp m_cmp;
    int m_queue_size = 0;
    std::vector<T> m_heap;
};
