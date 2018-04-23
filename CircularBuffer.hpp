/*
 * CircularBuffer.hpp
 *
 *  Created on: Apr 22, 2018
 *      Author: daniel
 */

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

template <typename T>
class CircularBuffer
{
public:
    typedef T data_t;
    CircularBuffer(int size) //;
    {
        m_iMaxSize = size;
        m_iNumElem = 0;
        m_iFront = 0;
        m_iBack = 0;
        m_Data = new data_t[size];
    }
    virtual ~CircularBuffer() //;
    {
        delete[] m_Data;
    }

    void push_back(data_t i_iElem)//;
    {
        m_Data[m_iBack] = i_iElem;
        m_iBack = (m_iBack + 1) % m_iMaxSize;

        if (m_iNumElem == m_iMaxSize) {
            m_iFront = (m_iFront + 1) % m_iMaxSize;
        } else {
            m_iNumElem++;
        }
    }

    data_t pop_front()//;
    {
        if (m_iNumElem == 0)
            return 0;

        data_t l_elem = m_Data[m_iFront];
        m_iFront = (m_iFront + 1) % m_iMaxSize;
        m_iNumElem--;
        return l_elem;
    }

    int num_elem()//;
    {
        return m_iNumElem;
    }

    data_t& operator[] (int index)//;
    {
        int l_RealIndex = (m_iFront + index) % m_iMaxSize;
        return m_Data[l_RealIndex];
    }

protected:
    data_t *m_Data;
    int m_iMaxSize;
    int m_iFront;
    int m_iBack;
    int m_iNumElem;


};

#endif /* CIRCULARBUFFER_HPP_ */
