#include "program.hpp"

/// @brief compared 2 strings on top of the stack
/// 
/// @return 0 strings are equal
/// @return !0 strings are not equal (see strcmp output)
///
int program::cmp_strings_on_stack_top() {
    // _stack sould have 2 strings at level 1 and 2
    // this function removes these 2 entries
    ostring* right = (ostring*)_stack->pop_back();
    ostring* left = (ostring*)_stack->pop_back();
    return strncmp(left->_value, right->_value, min(left->_len, right->_len));
}

/// @brief > keyword implementation
///
void program::rpn_sup(void) {
    MIN_ARGUMENTS(2);

    // numbers
    if (_stack->get_type(0) == cmd_number && _stack->get_type(1) == cmd_number) {
        number* right = (number*)_stack->pop_back();
        number* left = (number*)_stack->back();

        if (mpfr_cmp(left->_value.mpfr, right->_value.mpfr) > 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // strings
    else if (_stack->get_type(0) == cmd_string && _stack->get_type(1) == cmd_string) {
        int res_cmp = cmp_strings_on_stack_top();
        number* res = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        res->_value = (res_cmp > 0) ? 1L : 0L;
    } else
        ERR_CONTEXT(ret_bad_operand_type);
}

/// @brief >= keyword implementation
///
void program::rpn_sup_eq(void) {
    MIN_ARGUMENTS(2);

    // numbers
    if (_stack->get_type(0) == cmd_number && _stack->get_type(1) == cmd_number) {
        number* right = (number*)_stack->pop_back();
        number* left = (number*)_stack->back();

        if (mpfr_cmp(left->_value.mpfr, right->_value.mpfr) >= 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // strings
    else if (_stack->get_type(0) == cmd_string && _stack->get_type(1) == cmd_string) {
        int res_cmp = cmp_strings_on_stack_top();
        number* res = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        res->_value = (res_cmp >= 0) ? 1L : 0L;
    } else
        ERR_CONTEXT(ret_bad_operand_type);
}

/// @brief < keyword implementation
///
void program::rpn_inf(void) {
    MIN_ARGUMENTS(2);

    // numbers
    if (_stack->get_type(0) == cmd_number && _stack->get_type(1) == cmd_number) {
        number* right = (number*)_stack->pop_back();
        number* left = (number*)_stack->back();

        if (mpfr_cmp(left->_value.mpfr, right->_value.mpfr) < 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // strings
    else if (_stack->get_type(0) == cmd_string && _stack->get_type(1) == cmd_string) {
        int res_cmp = cmp_strings_on_stack_top();
        number* res = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        res->_value = (res_cmp < 0) ? 1L : 0L;
    } else
        ERR_CONTEXT(ret_bad_operand_type);
}

/// @brief <= keyword implementation
///
void program::rpn_inf_eq(void) {
    MIN_ARGUMENTS(2);

    // numbers
    if (_stack->get_type(0) == cmd_number && _stack->get_type(1) == cmd_number) {
        number* right = (number*)_stack->pop_back();
        number* left = (number*)_stack->back();

        if (mpfr_cmp(left->_value.mpfr, right->_value.mpfr) <= 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // strings
    else if (_stack->get_type(0) == cmd_string && _stack->get_type(1) == cmd_string) {
        int res_cmp = cmp_strings_on_stack_top();
        number* res = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        res->_value = (res_cmp <= 0) ? 1L : 0L;
    } else
        ERR_CONTEXT(ret_bad_operand_type);
}

/// @brief != keyword implementation
///
void program::rpn_diff(void) {
    MIN_ARGUMENTS(2);

    // numbers
    if (_stack->get_type(0) == cmd_number && _stack->get_type(1) == cmd_number) {
        number* right = (number*)_stack->pop_back();
        number* left = (number*)_stack->back();

        if (mpfr_cmp(left->_value.mpfr, right->_value.mpfr) != 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // complexes
    else if (_stack->get_type(0) == cmd_complex && _stack->get_type(1) == cmd_complex) {
        bool diff = false;
        complex* right = (complex*)_stack->pop_back();
        complex* left = (complex*)_stack->pop_back();

        if (mpfr_cmp(left->re()->mpfr, right->re()->mpfr) != 0 || mpfr_cmp(left->im()->mpfr, right->im()->mpfr) != 0)
            diff = true;

        number* num = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        if (diff)
            mpfr_set_si(num->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(num->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // strings
    else if (_stack->get_type(0) == cmd_string && _stack->get_type(1) == cmd_string) {
        int res_cmp = cmp_strings_on_stack_top();
        number* res = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        res->_value = (res_cmp != 0) ? 1L : 0L;
    } else
        ERR_CONTEXT(ret_bad_operand_type);
}

/// @brief == keyword implementation
///
void program::rpn_eq(void) {
    MIN_ARGUMENTS(2);

    // numbers
    if (_stack->get_type(0) == cmd_number && _stack->get_type(1) == cmd_number) {
        number* right = (number*)_stack->pop_back();
        number* left = (number*)_stack->back();

        if (mpfr_cmp(left->_value.mpfr, right->_value.mpfr) == 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
    // complexes
    else if (_stack->get_type(0) == cmd_complex && _stack->get_type(1) == cmd_complex) {
        bool diff = false;
        complex* right = (complex*)_stack->pop_back();
        complex* left = (complex*)_stack->pop_back();

        if (mpfr_cmp(left->re()->mpfr, right->re()->mpfr) != 0 || mpfr_cmp(left->im()->mpfr, right->im()->mpfr) != 0)
            diff = true;

        number* num = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        if (diff)
            mpfr_set_si(num->_value.mpfr, 0, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(num->_value.mpfr, 1, floating_t::s_mpfr_rnd);
    }
    // strings
    else if (_stack->get_type(0) == cmd_string && _stack->get_type(1) == cmd_string) {
        int res_cmp = cmp_strings_on_stack_top();
        number* res = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
        res->_value = (res_cmp == 0) ? 1L : 0L;
    } else
        ERR_CONTEXT(ret_bad_operand_type);
}

/// @brief and keyword implementation
///
void program::rpn_test_and(void) {
    MIN_ARGUMENTS(2);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);
    ARG_MUST_BE_OF_TYPE(1, cmd_number);

    number* right = (number*)_stack->pop_back();
    number* left = (number*)_stack->back();

    if ((mpfr_cmp_si(left->_value.mpfr, 0) != 0) && (mpfr_cmp_si(right->_value.mpfr, 0) != 0))
        mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
    else
        mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
}

/// @brief or keyword implementation
///
void program::rpn_test_or(void) {
    MIN_ARGUMENTS(2);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);
    ARG_MUST_BE_OF_TYPE(1, cmd_number);

    number* right = (number*)_stack->pop_back();
    number* left = (number*)_stack->back();

    if ((mpfr_cmp_si(left->_value.mpfr, 0) != 0) || (mpfr_cmp_si(right->_value.mpfr, 0) != 0))
        mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
    else
        mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
}

/// @brief xor keyword implementation
///
void program::rpn_test_xor(void) {
    MIN_ARGUMENTS(2);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);
    ARG_MUST_BE_OF_TYPE(1, cmd_number);

    number* right = (number*)_stack->pop_back();
    number* left = (number*)_stack->back();

    if (mpfr_cmp_si(left->_value.mpfr, 0) == 0) {
        if (mpfr_cmp_si(right->_value.mpfr, 0) != 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    } else {
        if (mpfr_cmp_si(right->_value.mpfr, 0) == 0)
            mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
        else
            mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
    }
}

/// @brief not keyword implementation
///
void program::rpn_test_not(void) {
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    number* left = (number*)_stack->back();
    if (mpfr_cmp_si(left->_value.mpfr, 0) == 0)
        mpfr_set_si(left->_value.mpfr, 1, floating_t::s_mpfr_rnd);
    else
        mpfr_set_si(left->_value.mpfr, 0, floating_t::s_mpfr_rnd);
}

/// @brief test same implementation
///
void program::rpn_same(void) { rpn_eq(); }
