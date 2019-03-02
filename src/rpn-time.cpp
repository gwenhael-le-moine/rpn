#include <time.h>
#include "program.hpp"

/// @brief time keyword implementation
///
void program::rpn_time() {
    struct timespec ts;
    struct tm* tm;

    // get local date
    clock_gettime(CLOCK_REALTIME, &ts);
    time_t time = (time_t)ts.tv_sec;
    tm = localtime(&time);
    if (tm != NULL) {
        double date;
        // date format = HH.MMSSssssss
        date = ((double)tm->tm_hour) * 10000000000.0 + ((double)tm->tm_min) * 100000000.0 +
               ((double)tm->tm_sec) * 1000000.0 + (double)(ts.tv_nsec / 1000);

        // push it
        number* num = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        CHECK_MPFR(mpfr_set_d(num->_value.mpfr, date, floating_t::s_mpfr_rnd));
        // division is done here because of real precision)
        CHECK_MPFR(mpfr_div_d(num->_value.mpfr, num->_value.mpfr, 10000000000.0, floating_t::s_mpfr_rnd));
    } else
        ERR_CONTEXT(ret_internal);
}

/// @brief date keyword implementation
///
void program::rpn_date() {
    struct timespec ts;
    struct tm* tm;

    // get local date
    clock_gettime(CLOCK_REALTIME, &ts);
    time_t time = (time_t)ts.tv_sec;
    tm = localtime(&time);
    if (tm != NULL) {
        double date;
        // date format = (M)M.DDYYYY
        date = (double)(tm->tm_mon + 1) * 1000000.0 + (double)(tm->tm_mday) * 10000.0 + (double)(tm->tm_year + 1900);

        // push it
        number* num = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        CHECK_MPFR(mpfr_set_d(num->_value.mpfr, date, floating_t::s_mpfr_rnd));
        // division is done here because of real precision)
        CHECK_MPFR(mpfr_div_d(num->_value.mpfr, num->_value.mpfr, 1000000.0, floating_t::s_mpfr_rnd));
    } else
        ERR_CONTEXT(ret_internal);
}

/// @brief ticks keyword implementation
///
void program::rpn_ticks() {
    struct timespec ts;
    struct tm* tm;

    // get local date
    clock_gettime(CLOCK_REALTIME, &ts);
    time_t time = (time_t)ts.tv_sec;
    tm = localtime(&time);
    if (tm != NULL) {
        double date;
        // date in µs
        date = 1000000.0 * (double)ts.tv_sec + (double)(ts.tv_nsec / 1000);

        // push it
        number* num = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        CHECK_MPFR(mpfr_set_d(num->_value.mpfr, date, floating_t::s_mpfr_rnd));
    } else
        ERR_CONTEXT(ret_internal);
}
