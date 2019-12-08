/* 47 terminals 71 non_terminals 67 actions (31 duplicates) 691 parse table entries */

#if !defined(GRAMMAR_TABLE) && !defined(TOKEN_NAMES) && !defined(PARSE_CODE)
typedef enum {
    TOKEN_NONE = 0,
    END = 1,
    DEF = 2,
    NAME = 3,
    OP = 4,
    CP = 5,
    COLON = 6,
    IMPORT = 7,
    COMMA = 8,
    ASSIGN = 9,
    NL = 10,
    SEMI = 11,
    RETURN = 12,
    BREAK = 13,
    CONTINUE = 14,
    PASS = 15,
    GLOBAL = 16,
    DEL = 17,
    ASSERT = 18,
    IF = 19,
    ELIF = 20,
    ELSE = 21,
    WHILE = 22,
    FOR = 23,
    IN = 24,
    RANGE = 25,
    INDENT = 26,
    EXDENT = 27,
    OR = 28,
    AND = 29,
    NOT = 30,
    IS = 31,
    CMPOP = 32,
    LOR = 33,
    LAND = 34,
    LXOR = 35,
    SHIFT = 36,
    PLUS = 37,
    MINUS = 38,
    MULOP = 39,
    LNOT = 40,
    POW = 41,
    OS = 42,
    CS = 43,
    OC = 44,
    CC = 45,
    NUMBER = 46,
    STRING = 47,
    FIRST_NON_TERMINAL = 48,
    NON_TERMINAL_start = 48,
    NON_TERMINAL_command = 49,
    NON_TERMINAL_opt_formals = 50,
    NON_TERMINAL_formals = 51,
    NON_TERMINAL_formals_p = 52,
    NON_TERMINAL_formal = 53,
    NON_TERMINAL_opt_named_p = 54,
    NON_TERMINAL_opt_stats = 55,
    NON_TERMINAL_stat = 56,
    NON_TERMINAL_simple_stat = 57,
    NON_TERMINAL_small_stats_p = 58,
    NON_TERMINAL_small_stat = 59,
    NON_TERMINAL_dels_p = 60,
    NON_TERMINAL_del = 61,
    NON_TERMINAL_ret_expr = 62,
    NON_TERMINAL_assign_expr = 63,
    NON_TERMINAL_assign_expr_p = 64,
    NON_TERMINAL_globals = 65,
    NON_TERMINAL_globals_p = 66,
    NON_TERMINAL_global = 67,
    NON_TERMINAL_compound_stat = 68,
    NON_TERMINAL_if_stat = 69,
    NON_TERMINAL_elif_stats = 70,
    NON_TERMINAL_if_expr = 71,
    NON_TERMINAL_while_stat = 72,
    NON_TERMINAL_while_else_stat = 73,
    NON_TERMINAL_for_stat = 74,
    NON_TERMINAL_for_params = 75,
    NON_TERMINAL_suite = 76,
    NON_TERMINAL_expr = 77,
    NON_TERMINAL_expr_or_p = 78,
    NON_TERMINAL_expr_and = 79,
    NON_TERMINAL_expr_and_p = 80,
    NON_TERMINAL_expr_not = 81,
    NON_TERMINAL_expr_cmp = 82,
    NON_TERMINAL_expr_cmp_p = 83,
    NON_TERMINAL_cmpop = 84,
    NON_TERMINAL_expr_lor = 85,
    NON_TERMINAL_expr_lor_p = 86,
    NON_TERMINAL_expr_land = 87,
    NON_TERMINAL_expr_land_p = 88,
    NON_TERMINAL_expr_lxor = 89,
    NON_TERMINAL_expr_lxor_p = 90,
    NON_TERMINAL_expr_shift = 91,
    NON_TERMINAL_expr_shift_p = 92,
    NON_TERMINAL_expr_add = 93,
    NON_TERMINAL_expr_add_p = 94,
    NON_TERMINAL_expr_mul = 95,
    NON_TERMINAL_expr_mul_p = 96,
    NON_TERMINAL_expr_unary = 97,
    NON_TERMINAL_expr_pow = 98,
    NON_TERMINAL_expr_pow_p = 99,
    NON_TERMINAL_expr_array = 100,
    NON_TERMINAL_expr_array_p = 101,
    NON_TERMINAL_array_index = 102,
    NON_TERMINAL_opt_slice = 103,
    NON_TERMINAL_slice = 104,
    NON_TERMINAL_slice_p = 105,
    NON_TERMINAL_opt_expr = 106,
    NON_TERMINAL_expr_prim = 107,
    NON_TERMINAL_strings_p = 108,
    NON_TERMINAL_opt_tuple = 109,
    NON_TERMINAL_opt_tuple_p = 110,
    NON_TERMINAL_opt_actuals = 111,
    NON_TERMINAL_actuals = 112,
    NON_TERMINAL_actual_p = 113,
    NON_TERMINAL_actuals_p = 114,
    NON_TERMINAL_opt_dict_ents = 115,
    NON_TERMINAL_dict_ents_p = 116,
    NON_TERMINAL_dict_ent = 117,
    NON_TERMINAL_dict_ent_p = 118,
    FIRST_ACTION = 119,
    ACTION_119 = 119, // goto patch_loop;
    ACTION_120 = 120, // goto unop_first;
    ACTION_121 = 121, // goto else_branch;
    ACTION_122 = 122, // goto binop_first;
    ACTION_123 = 123, // goto unop_second;
    ACTION_124 = 124, // goto short_second;
    ACTION_125 = 125, // goto binop_second;
    ACTION_126 = 126, // { goto add_op_lvalue; }
    ACTION_127 = 127, // { value_push_offset(0); }
    ACTION_128 = 128, // { value_push_bool(true); }
    ACTION_129 = 129, // { value_push_bool(false); }
    ACTION_130 = 130, // { snek_parse_middle = false; }
    ACTION_131 = 131, // { value_push_op(snek_op_uminus); }
    ACTION_132 = 132, // { snek_code_add_op(snek_op_null); }
    ACTION_133 = 133, // { value_push_id(snek_token_val.id); }
    ACTION_134 = 134, // { snek_code_add_op(snek_op_return); }
    ACTION_135 = 135, // { snek_code_add_op(snek_op_assert); }
    ACTION_136 = 136, // { snek_print_val = snek_interactive; }
    ACTION_137 = 137, // { value_push_offset(snek_code_current()); }
    ACTION_138 = 138, // { value_push_indent(snek_token_val.indent); }
    ACTION_139 = 139, // { snek_code_add_forward(snek_forward_break); }
    ACTION_140 = 140, // { snek_code_set_push(snek_code_prev_insn()); }
    ACTION_141 = 141, // { snek_code_add_number(snek_token_val.number); }
    ACTION_142 = 142, // { snek_code_add_string(snek_token_val.string); }
    ACTION_143 = 143, // { value_push_offset(0); value_push_bool(true); }
    ACTION_144 = 144, // { snek_code_add_forward(snek_forward_continue); }
    ACTION_145 = 145, // { unop_first: value_push_op(snek_token_val.op); }
    ACTION_146 = 146, // { snek_parse_nformal = 0; snek_parse_nnamed = 0; }
    ACTION_147 = 147, // { unop_second: snek_code_add_op(value_pop().op); }
    ACTION_148 = 148, // { binop_second: snek_code_add_op(value_pop().op); }
    ACTION_149 = 149, // { if (snek_parse_nnamed) return parse_return_syntax; }
    ACTION_150 = 150, // { snek_code_add_op_id(snek_op_id, snek_token_val.id); }
    ACTION_151 = 151, // { snek_code_add_op_offset(snek_op_line, snek_lex_line); }
    ACTION_152 = 152, // { snek_token_val.op = snek_op_del; goto extract_lvalue; }
    ACTION_153 = 153, // { snek_code_add_op_id(snek_op_global, snek_token_val.id); }
    ACTION_154 = 154, // { snek_code_add_op_offset(snek_op_call, value_pop().offset); }
    ACTION_155 = 155, // { snek_parse_formals[snek_parse_nformal++] = snek_token_val.id; }
    ACTION_156 = 156, // { snek_code_set_push(snek_code_prev_insn()); value_push_bool(true); }
    ACTION_157 = 157, // { snek_print_val = false; snek_code_add_op_offset(snek_op_line, snek_lex_line); }
    ACTION_158 = 158, // { snek_offset_t num = value_pop().offset; snek_code_add_op_offset(snek_op_dict, num); }
    ACTION_159 = 159, // { snek_code_set_push(snek_code_prev_insn()); value_push_offset(value_pop().offset + 1); }
    ACTION_160 = 160, // { snek_code_add_op_offset(snek_op_branch_true, 0); value_push_offset(snek_compile_prev); }
    ACTION_161 = 161, // { snek_code_add_op_offset(snek_op_branch_false, 0); value_push_offset(snek_compile_prev); }
    ACTION_162 = 162, // { snek_code_set_push(snek_code_prev_insn()); value_push_offset(value_pop().offset + 256); }
    ACTION_163 = 163, // { snek_id_t id = value_pop().id; snek_code_add_in_enum(id, for_depth); goto for_push_prevs; }
    ACTION_164 = 164, // { binop_first: snek_code_set_push(snek_code_prev_insn()); value_push_op(snek_token_val.op); }
    ACTION_165 = 165, // { snek_parse_nnamed++; snek_code_add_op_id(snek_op_assign_named, snek_parse_formals[snek_parse_nformal-1]); }
    ACTION_166 = 166, // { short_second: snek_code_patch_branch(value_pop().offset, snek_code_current()); snek_code_add_op(snek_op_nop); }
    ACTION_167 = 167, // { add_op_lvalue:; snek_op_t op = value_pop().offset; snek_id_t id = value_pop().id; snek_code_add_op_id(op, id); }
    ACTION_168 = 168, // { snek_code_set_push(snek_code_prev_insn()); snek_code_add_string(snek_token_val.string); snek_code_add_op(snek_op_plus); }
    ACTION_169 = 169, // { snek_code_add_op_offset(snek_op_branch, 0); value_push_offset(snek_compile_prev); value_push_offset(snek_code_current()); }
    ACTION_170 = 170, // { snek_offset_t num = value_pop().offset; if (num >= 256) return parse_return_syntax; snek_code_add_op_offset(snek_op_list, num); }
    ACTION_171 = 171, // { bool tuple = value_pop().bools; if (tuple) { snek_offset_t num = value_pop().offset; snek_code_add_op_offset(snek_op_tuple, num); } }
    ACTION_172 = 172, // { snek_code_add_op_offset(snek_op_branch, 0); value_push_offset(snek_compile_prev); value_push_offset(snek_code_current()); for_depth--; }
    ACTION_173 = 173, // { snek_offset_t num = value_pop().offset; if (num >= 256) return parse_return_syntax; value_push_offset(num + 1); value_push_bool(true); }
    ACTION_174 = 174, // { snek_code_add_op_offset(snek_op_line, snek_lex_line); else_branch: snek_code_add_forward(snek_forward_if); value_push_offset(snek_code_current()); }
    ACTION_175 = 175, // { snek_offset_t elif_stats_off = value_pop().offset; snek_offset_t if_expr_off = value_pop().offset; snek_code_patch_branch(if_expr_off, elif_stats_off); }
    ACTION_176 = 176, // { snek_offset_t offset = value_pop().offset; if (offset >= 256) return parse_return_syntax; value_push_offset(offset + 1); snek_code_set_push(snek_code_prev_insn()); }
    ACTION_177 = 177, // { snek_offset_t elif_stats_off = value_pop().offset; snek_offset_t if_expr_off = value_pop().offset; snek_code_patch_branch(if_expr_off, elif_stats_off); snek_code_patch_forward(if_expr_off, snek_compile_size, snek_forward_if, snek_code_current()); }
    ACTION_178 = 178, // { uint8_t indent = value_pop().indent; uint8_t exdent = snek_token_val.indent; snek_current_indent = indent; if (exdent > snek_current_indent) { snek_error("mismatching indentation indent %d exdent %d", indent, exdent); return parse_return_syntax; } }
    ACTION_179 = 179, // { snek_code_t *code = snek_code_finish(); SNEK_CODE_HOOK_START snek_poly_t p = snek_exec(code); SNEK_CODE_HOOK_STOP if (snek_abort) return parse_return_error; if (snek_print_val && !snek_is_null(p)) { snek_poly_print(stdout, p, 'r'); putchar('\n'); } }
    ACTION_180 = 180, // { snek_offset_t num = value_pop().offset; if (num >= 256) return parse_return_syntax; snek_id_t id = value_pop().id; snek_code_add_in_range(id, num, for_depth); for_push_prevs: value_push_offset(snek_compile_prev); value_push_offset(snek_compile_prev); for_depth++; }
    ACTION_181 = 181, // { bool slice = value_pop().bools; if (slice) { snek_code_set_push(snek_code_prev_insn()); uint8_t stride = value_pop().bools * SNEK_OP_SLICE_STRIDE; uint8_t end = value_pop().bools * SNEK_OP_SLICE_END; uint8_t start = value_pop().bools * SNEK_OP_SLICE_START; snek_code_add_slice(start | end | stride); } else { snek_code_add_op(snek_op_array); } }
    ACTION_182 = 182, // { snek_offset_t prev_offset = snek_code_prev_insn(); uint8_t *prev = snek_code_at(prev_offset); snek_id_t id; /* look at the previous instruction to figure out * if it's an id. */ if (*prev != snek_op_id) return parse_return_syntax; memcpy(&id, prev + 1, sizeof (snek_id_t)); snek_code_delete_prev(); snek_code_add_number(id); snek_code_set_push(snek_code_prev_insn()); }
    ACTION_183 = 183, // { if (snek_compile[snek_compile_prev] == snek_op_return) snek_code_delete_prev(); else snek_code_add_op(snek_op_null); snek_code_t *code = snek_code_finish(); if (!code) break; snek_func_t *func = snek_func_alloc(code); if (!func) break; snek_poly_t poly = snek_func_to_poly(func); snek_id_t id = value_pop().id; snek_stack_push(poly); snek_poly_t *ref = snek_id_ref(id, true); poly = snek_stack_pop(); if (ref) *ref = poly; }
    ACTION_184 = 184, // { patch_loop:; snek_offset_t while_else_stat_off = value_pop().offset; snek_offset_t loop_end_off = value_pop().offset; snek_offset_t while_off = value_pop().offset; snek_offset_t top_off = value_pop().offset; snek_code_patch_branch(while_off, while_else_stat_off); snek_code_patch_branch(loop_end_off, top_off); snek_code_patch_forward(while_off, loop_end_off, snek_forward_continue, top_off); snek_code_patch_forward(while_off, loop_end_off, snek_forward_break, snek_code_current()); }
    ACTION_185 = 185, // { extract_lvalue: snek_print_val = false; snek_offset_t prev_offset = snek_code_prev_insn(); uint8_t *prev = snek_code_at(prev_offset); snek_id_t id; /* look at the previous instruction to figure out what * it was -- an id or an array. All others are illegal */ switch (*prev) { case snek_op_id: memcpy(&id, prev + 1, sizeof (snek_id_t)); break; case snek_op_array: if (snek_token_val.op != snek_op_del) snek_code_set_push(snek_code_prev_prev_insn()); id = SNEK_ID_NONE; break; default: return parse_return_syntax; } value_push_id(id); value_push_offset(snek_token_val.op); /* eliminate the previous instruction having * extracted the useful information from it */ snek_code_delete_prev(); }
} __attribute__((packed)) token_t;
#endif

#ifdef GRAMMAR_TABLE
#undef GRAMMAR_TABLE
#ifndef PARSE_TABLE_DECLARATION
#define PARSE_TABLE_DECLARATION(n) n
#endif
/*
 * Parse table
 *
 * LNOT        , start        command, ACTION_130, start,
 * MINUS       , start        command, ACTION_130, start,
 * PLUS        , start        command, ACTION_130, start,
 * OP          , start        command, ACTION_130, start,
 * OS          , start        command, ACTION_130, start,
 * OC          , start        command, ACTION_130, start,
 * NAME        , start        command, ACTION_130, start,
 * NUMBER      , start        command, ACTION_130, start,
 * STRING      , start        command, ACTION_130, start,
 * NOT         , start        command, ACTION_130, start,
 * RETURN      , start        command, ACTION_130, start,
 * BREAK       , start        command, ACTION_130, start,
 * CONTINUE    , start        command, ACTION_130, start,
 * PASS        , start        command, ACTION_130, start,
 * GLOBAL      , start        command, ACTION_130, start,
 * DEL         , start        command, ACTION_130, start,
 * ASSERT      , start        command, ACTION_130, start,
 * IF          , start        command, ACTION_130, start,
 * WHILE       , start        command, ACTION_130, start,
 * FOR         , start        command, ACTION_130, start,
 * NL          , start        command, ACTION_130, start,
 * DEF         , start        command, ACTION_130, start,
 * IMPORT      , start        command, ACTION_130, start,
 * END         , start       ()
 * LNOT        , command      ACTION_136, stat, ACTION_179,
 * MINUS       , command      ACTION_136, stat, ACTION_179,
 * PLUS        , command      ACTION_136, stat, ACTION_179,
 * OP          , command      ACTION_136, stat, ACTION_179,
 * OS          , command      ACTION_136, stat, ACTION_179,
 * OC          , command      ACTION_136, stat, ACTION_179,
 * NAME        , command      ACTION_136, stat, ACTION_179,
 * NUMBER      , command      ACTION_136, stat, ACTION_179,
 * STRING      , command      ACTION_136, stat, ACTION_179,
 * NOT         , command      ACTION_136, stat, ACTION_179,
 * RETURN      , command      ACTION_136, stat, ACTION_179,
 * BREAK       , command      ACTION_136, stat, ACTION_179,
 * CONTINUE    , command      ACTION_136, stat, ACTION_179,
 * PASS        , command      ACTION_136, stat, ACTION_179,
 * GLOBAL      , command      ACTION_136, stat, ACTION_179,
 * DEL         , command      ACTION_136, stat, ACTION_179,
 * ASSERT      , command      ACTION_136, stat, ACTION_179,
 * IF          , command      ACTION_136, stat, ACTION_179,
 * WHILE       , command      ACTION_136, stat, ACTION_179,
 * FOR         , command      ACTION_136, stat, ACTION_179,
 * NL          , command      ACTION_136, stat, ACTION_179,
 * DEF         , command      DEF, ACTION_146, NAME, ACTION_133, OP, opt-formals, CP, COLON, suite, ACTION_183,
 * IMPORT      , command      IMPORT, NAME,
 * NAME        , opt-formals  formals,
 * CP          , opt-formals ()
 * NAME        , formals      formal, formals-p,
 * COMMA       , formals-p    COMMA, formal, formals-p,
 * CP          , formals-p   ()
 * NAME        , formal       NAME, ACTION_155, opt-named-p,
 * ASSIGN      , opt-named-p  ASSIGN, expr, ACTION_165,
 * COMMA       , opt-named-p  ACTION_149,
 * CP          , opt-named-p  ACTION_149,
 * LNOT        , opt-stats    stat, opt-stats,
 * MINUS       , opt-stats    stat, opt-stats,
 * PLUS        , opt-stats    stat, opt-stats,
 * OP          , opt-stats    stat, opt-stats,
 * OS          , opt-stats    stat, opt-stats,
 * OC          , opt-stats    stat, opt-stats,
 * NAME        , opt-stats    stat, opt-stats,
 * NUMBER      , opt-stats    stat, opt-stats,
 * STRING      , opt-stats    stat, opt-stats,
 * NOT         , opt-stats    stat, opt-stats,
 * RETURN      , opt-stats    stat, opt-stats,
 * BREAK       , opt-stats    stat, opt-stats,
 * CONTINUE    , opt-stats    stat, opt-stats,
 * PASS        , opt-stats    stat, opt-stats,
 * GLOBAL      , opt-stats    stat, opt-stats,
 * DEL         , opt-stats    stat, opt-stats,
 * ASSERT      , opt-stats    stat, opt-stats,
 * IF          , opt-stats    stat, opt-stats,
 * WHILE       , opt-stats    stat, opt-stats,
 * FOR         , opt-stats    stat, opt-stats,
 * NL          , opt-stats    stat, opt-stats,
 * EXDENT      , opt-stats   ()
 * LNOT        , stat         simple-stat,
 * MINUS       , stat         simple-stat,
 * PLUS        , stat         simple-stat,
 * OP          , stat         simple-stat,
 * OS          , stat         simple-stat,
 * OC          , stat         simple-stat,
 * NAME        , stat         simple-stat,
 * NUMBER      , stat         simple-stat,
 * STRING      , stat         simple-stat,
 * NOT         , stat         simple-stat,
 * RETURN      , stat         simple-stat,
 * BREAK       , stat         simple-stat,
 * CONTINUE    , stat         simple-stat,
 * PASS        , stat         simple-stat,
 * GLOBAL      , stat         simple-stat,
 * DEL         , stat         simple-stat,
 * ASSERT      , stat         simple-stat,
 * IF          , stat         ACTION_157, compound-stat,
 * WHILE       , stat         ACTION_157, compound-stat,
 * FOR         , stat         ACTION_157, compound-stat,
 * NL          , stat         NL,
 * LNOT        , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * MINUS       , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * PLUS        , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * OP          , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * OS          , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * OC          , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * NAME        , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * NUMBER      , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * STRING      , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * NOT         , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * RETURN      , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * BREAK       , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * CONTINUE    , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * PASS        , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * GLOBAL      , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * DEL         , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * ASSERT      , simple-stat  ACTION_151, small-stat, small-stats-p, NL,
 * SEMI        , small-stats-p SEMI, small-stat, small-stats-p,
 * NL          , small-stats-p()
 * LNOT        , small-stat   assign-expr,
 * MINUS       , small-stat   assign-expr,
 * PLUS        , small-stat   assign-expr,
 * OP          , small-stat   assign-expr,
 * OS          , small-stat   assign-expr,
 * OC          , small-stat   assign-expr,
 * NAME        , small-stat   assign-expr,
 * NUMBER      , small-stat   assign-expr,
 * STRING      , small-stat   assign-expr,
 * NOT         , small-stat   assign-expr,
 * RETURN      , small-stat   RETURN, ret-expr, ACTION_134,
 * BREAK       , small-stat   BREAK, ACTION_139,
 * CONTINUE    , small-stat   CONTINUE, ACTION_144,
 * PASS        , small-stat   PASS,
 * GLOBAL      , small-stat   GLOBAL, globals,
 * DEL         , small-stat   DEL, del, dels-p,
 * ASSERT      , small-stat   ASSERT, expr, ACTION_135,
 * COMMA       , dels-p       COMMA, del, dels-p,
 * SEMI        , dels-p      ()
 * NL          , dels-p      ()
 * OP          , del          expr-array, ACTION_152, ACTION_126,
 * OS          , del          expr-array, ACTION_152, ACTION_126,
 * OC          , del          expr-array, ACTION_152, ACTION_126,
 * NAME        , del          expr-array, ACTION_152, ACTION_126,
 * NUMBER      , del          expr-array, ACTION_152, ACTION_126,
 * STRING      , del          expr-array, ACTION_152, ACTION_126,
 * LNOT        , ret-expr     expr,
 * MINUS       , ret-expr     expr,
 * PLUS        , ret-expr     expr,
 * OP          , ret-expr     expr,
 * OS          , ret-expr     expr,
 * OC          , ret-expr     expr,
 * NAME        , ret-expr     expr,
 * NUMBER      , ret-expr     expr,
 * STRING      , ret-expr     expr,
 * NOT         , ret-expr     expr,
 * SEMI        , ret-expr     ACTION_132,
 * NL          , ret-expr     ACTION_132,
 * LNOT        , assign-expr  expr, assign-expr-p,
 * MINUS       , assign-expr  expr, assign-expr-p,
 * PLUS        , assign-expr  expr, assign-expr-p,
 * OP          , assign-expr  expr, assign-expr-p,
 * OS          , assign-expr  expr, assign-expr-p,
 * OC          , assign-expr  expr, assign-expr-p,
 * NAME        , assign-expr  expr, assign-expr-p,
 * NUMBER      , assign-expr  expr, assign-expr-p,
 * STRING      , assign-expr  expr, assign-expr-p,
 * NOT         , assign-expr  expr, assign-expr-p,
 * ASSIGN      , assign-expr-p ASSIGN, ACTION_185, expr, ACTION_167,
 * SEMI        , assign-expr-p()
 * NL          , assign-expr-p()
 * NAME        , globals      global, globals-p,
 * SEMI        , globals     ()
 * NL          , globals     ()
 * COMMA       , globals-p    COMMA, global, globals-p,
 * SEMI        , globals-p   ()
 * NL          , globals-p   ()
 * NAME        , global       NAME, ACTION_153,
 * IF          , compound-stat if-stat,
 * WHILE       , compound-stat while-stat,
 * FOR         , compound-stat for-stat,
 * IF          , if-stat      IF, if-expr, suite, elif-stats, ACTION_177,
 * ELIF        , elif-stats   ELIF, ACTION_174, if-expr, suite, elif-stats, ACTION_175,
 * ELSE        , elif-stats   ELSE, COLON, ACTION_121, suite,
 * DEF         , elif-stats   ACTION_137,
 * IMPORT      , elif-stats   ACTION_137,
 * END         , elif-stats   ACTION_137,
 * LNOT        , elif-stats   ACTION_137,
 * MINUS       , elif-stats   ACTION_137,
 * PLUS        , elif-stats   ACTION_137,
 * OP          , elif-stats   ACTION_137,
 * OS          , elif-stats   ACTION_137,
 * OC          , elif-stats   ACTION_137,
 * NAME        , elif-stats   ACTION_137,
 * NUMBER      , elif-stats   ACTION_137,
 * STRING      , elif-stats   ACTION_137,
 * NOT         , elif-stats   ACTION_137,
 * RETURN      , elif-stats   ACTION_137,
 * BREAK       , elif-stats   ACTION_137,
 * CONTINUE    , elif-stats   ACTION_137,
 * PASS        , elif-stats   ACTION_137,
 * GLOBAL      , elif-stats   ACTION_137,
 * DEL         , elif-stats   ACTION_137,
 * ASSERT      , elif-stats   ACTION_137,
 * IF          , elif-stats   ACTION_137,
 * WHILE       , elif-stats   ACTION_137,
 * FOR         , elif-stats   ACTION_137,
 * NL          , elif-stats   ACTION_137,
 * EXDENT      , elif-stats   ACTION_137,
 * LNOT        , if-expr      expr, COLON, ACTION_161,
 * MINUS       , if-expr      expr, COLON, ACTION_161,
 * PLUS        , if-expr      expr, COLON, ACTION_161,
 * OP          , if-expr      expr, COLON, ACTION_161,
 * OS          , if-expr      expr, COLON, ACTION_161,
 * OC          , if-expr      expr, COLON, ACTION_161,
 * NAME        , if-expr      expr, COLON, ACTION_161,
 * NUMBER      , if-expr      expr, COLON, ACTION_161,
 * STRING      , if-expr      expr, COLON, ACTION_161,
 * NOT         , if-expr      expr, COLON, ACTION_161,
 * WHILE       , while-stat   ACTION_137, WHILE, expr, COLON, ACTION_161, suite, ACTION_169, while-else-stat, ACTION_184,
 * ELSE        , while-else-stat ELSE, COLON, suite,
 * DEF         , while-else-stat()
 * IMPORT      , while-else-stat()
 * END         , while-else-stat()
 * LNOT        , while-else-stat()
 * MINUS       , while-else-stat()
 * PLUS        , while-else-stat()
 * OP          , while-else-stat()
 * OS          , while-else-stat()
 * OC          , while-else-stat()
 * NAME        , while-else-stat()
 * NUMBER      , while-else-stat()
 * STRING      , while-else-stat()
 * NOT         , while-else-stat()
 * RETURN      , while-else-stat()
 * BREAK       , while-else-stat()
 * CONTINUE    , while-else-stat()
 * PASS        , while-else-stat()
 * GLOBAL      , while-else-stat()
 * DEL         , while-else-stat()
 * ASSERT      , while-else-stat()
 * IF          , while-else-stat()
 * WHILE       , while-else-stat()
 * FOR         , while-else-stat()
 * NL          , while-else-stat()
 * EXDENT      , while-else-stat()
 * FOR         , for-stat     FOR, NAME, ACTION_133, IN, for-params, suite, ACTION_172, while-else-stat, ACTION_119,
 * RANGE       , for-params   RANGE, OP, opt-actuals, CP, COLON, ACTION_180,
 * LNOT        , for-params   expr, COLON, ACTION_163,
 * MINUS       , for-params   expr, COLON, ACTION_163,
 * PLUS        , for-params   expr, COLON, ACTION_163,
 * OP          , for-params   expr, COLON, ACTION_163,
 * OS          , for-params   expr, COLON, ACTION_163,
 * OC          , for-params   expr, COLON, ACTION_163,
 * NAME        , for-params   expr, COLON, ACTION_163,
 * NUMBER      , for-params   expr, COLON, ACTION_163,
 * STRING      , for-params   expr, COLON, ACTION_163,
 * NOT         , for-params   expr, COLON, ACTION_163,
 * LNOT        , suite        simple-stat,
 * MINUS       , suite        simple-stat,
 * PLUS        , suite        simple-stat,
 * OP          , suite        simple-stat,
 * OS          , suite        simple-stat,
 * OC          , suite        simple-stat,
 * NAME        , suite        simple-stat,
 * NUMBER      , suite        simple-stat,
 * STRING      , suite        simple-stat,
 * NOT         , suite        simple-stat,
 * RETURN      , suite        simple-stat,
 * BREAK       , suite        simple-stat,
 * CONTINUE    , suite        simple-stat,
 * PASS        , suite        simple-stat,
 * GLOBAL      , suite        simple-stat,
 * DEL         , suite        simple-stat,
 * ASSERT      , suite        simple-stat,
 * NL          , suite        NL, INDENT, ACTION_138, stat, opt-stats, EXDENT, ACTION_178,
 * LNOT        , expr         expr-and, expr-or-p,
 * MINUS       , expr         expr-and, expr-or-p,
 * PLUS        , expr         expr-and, expr-or-p,
 * OP          , expr         expr-and, expr-or-p,
 * OS          , expr         expr-and, expr-or-p,
 * OC          , expr         expr-and, expr-or-p,
 * NAME        , expr         expr-and, expr-or-p,
 * NUMBER      , expr         expr-and, expr-or-p,
 * STRING      , expr         expr-and, expr-or-p,
 * NOT         , expr         expr-and, expr-or-p,
 * OR          , expr-or-p    OR, ACTION_160, expr-and, ACTION_166, expr-or-p,
 * SEMI        , expr-or-p   ()
 * NL          , expr-or-p   ()
 * ASSIGN      , expr-or-p   ()
 * CS          , expr-or-p   ()
 * CP          , expr-or-p   ()
 * COLON       , expr-or-p   ()
 * COMMA       , expr-or-p   ()
 * CC          , expr-or-p   ()
 * LNOT        , expr-and     expr-not, expr-and-p,
 * MINUS       , expr-and     expr-not, expr-and-p,
 * PLUS        , expr-and     expr-not, expr-and-p,
 * OP          , expr-and     expr-not, expr-and-p,
 * OS          , expr-and     expr-not, expr-and-p,
 * OC          , expr-and     expr-not, expr-and-p,
 * NAME        , expr-and     expr-not, expr-and-p,
 * NUMBER      , expr-and     expr-not, expr-and-p,
 * STRING      , expr-and     expr-not, expr-and-p,
 * NOT         , expr-and     expr-not, expr-and-p,
 * AND         , expr-and-p   AND, ACTION_161, expr-not, ACTION_124, expr-and-p,
 * OR          , expr-and-p  ()
 * SEMI        , expr-and-p  ()
 * NL          , expr-and-p  ()
 * ASSIGN      , expr-and-p  ()
 * CS          , expr-and-p  ()
 * CP          , expr-and-p  ()
 * COLON       , expr-and-p  ()
 * COMMA       , expr-and-p  ()
 * CC          , expr-and-p  ()
 * LNOT        , expr-not     expr-cmp,
 * MINUS       , expr-not     expr-cmp,
 * PLUS        , expr-not     expr-cmp,
 * OP          , expr-not     expr-cmp,
 * OS          , expr-not     expr-cmp,
 * OC          , expr-not     expr-cmp,
 * NAME        , expr-not     expr-cmp,
 * NUMBER      , expr-not     expr-cmp,
 * STRING      , expr-not     expr-cmp,
 * NOT         , expr-not     NOT, ACTION_145, expr-not, ACTION_147,
 * LNOT        , expr-cmp     expr-lor, expr-cmp-p,
 * MINUS       , expr-cmp     expr-lor, expr-cmp-p,
 * PLUS        , expr-cmp     expr-lor, expr-cmp-p,
 * OP          , expr-cmp     expr-lor, expr-cmp-p,
 * OS          , expr-cmp     expr-lor, expr-cmp-p,
 * OC          , expr-cmp     expr-lor, expr-cmp-p,
 * NAME        , expr-cmp     expr-lor, expr-cmp-p,
 * NUMBER      , expr-cmp     expr-lor, expr-cmp-p,
 * STRING      , expr-cmp     expr-lor, expr-cmp-p,
 * CMPOP       , expr-cmp-p   cmpop, ACTION_164, expr-lor, ACTION_148, expr-cmp-p,
 * IN          , expr-cmp-p   cmpop, ACTION_164, expr-lor, ACTION_148, expr-cmp-p,
 * IS          , expr-cmp-p   IS, ACTION_122, expr-lor, ACTION_125, expr-cmp-p,
 * AND         , expr-cmp-p  ()
 * OR          , expr-cmp-p  ()
 * SEMI        , expr-cmp-p  ()
 * NL          , expr-cmp-p  ()
 * ASSIGN      , expr-cmp-p  ()
 * CS          , expr-cmp-p  ()
 * CP          , expr-cmp-p  ()
 * COLON       , expr-cmp-p  ()
 * COMMA       , expr-cmp-p  ()
 * CC          , expr-cmp-p  ()
 * CMPOP       , cmpop        CMPOP,
 * IN          , cmpop        IN,
 * LNOT        , expr-lor     expr-land, expr-lor-p,
 * MINUS       , expr-lor     expr-land, expr-lor-p,
 * PLUS        , expr-lor     expr-land, expr-lor-p,
 * OP          , expr-lor     expr-land, expr-lor-p,
 * OS          , expr-lor     expr-land, expr-lor-p,
 * OC          , expr-lor     expr-land, expr-lor-p,
 * NAME        , expr-lor     expr-land, expr-lor-p,
 * NUMBER      , expr-lor     expr-land, expr-lor-p,
 * STRING      , expr-lor     expr-land, expr-lor-p,
 * LOR         , expr-lor-p   LOR, ACTION_122, expr-land, ACTION_125, expr-lor-p,
 * CMPOP       , expr-lor-p  ()
 * IN          , expr-lor-p  ()
 * IS          , expr-lor-p  ()
 * AND         , expr-lor-p  ()
 * OR          , expr-lor-p  ()
 * SEMI        , expr-lor-p  ()
 * NL          , expr-lor-p  ()
 * ASSIGN      , expr-lor-p  ()
 * CS          , expr-lor-p  ()
 * CP          , expr-lor-p  ()
 * COLON       , expr-lor-p  ()
 * COMMA       , expr-lor-p  ()
 * CC          , expr-lor-p  ()
 * LNOT        , expr-land    expr-lxor, expr-land-p,
 * MINUS       , expr-land    expr-lxor, expr-land-p,
 * PLUS        , expr-land    expr-lxor, expr-land-p,
 * OP          , expr-land    expr-lxor, expr-land-p,
 * OS          , expr-land    expr-lxor, expr-land-p,
 * OC          , expr-land    expr-lxor, expr-land-p,
 * NAME        , expr-land    expr-lxor, expr-land-p,
 * NUMBER      , expr-land    expr-lxor, expr-land-p,
 * STRING      , expr-land    expr-lxor, expr-land-p,
 * LAND        , expr-land-p  LAND, ACTION_122, expr-lxor, ACTION_125, expr-land-p,
 * LOR         , expr-land-p ()
 * CMPOP       , expr-land-p ()
 * IN          , expr-land-p ()
 * IS          , expr-land-p ()
 * AND         , expr-land-p ()
 * OR          , expr-land-p ()
 * SEMI        , expr-land-p ()
 * NL          , expr-land-p ()
 * ASSIGN      , expr-land-p ()
 * CS          , expr-land-p ()
 * CP          , expr-land-p ()
 * COLON       , expr-land-p ()
 * COMMA       , expr-land-p ()
 * CC          , expr-land-p ()
 * LNOT        , expr-lxor    expr-shift, expr-lxor-p,
 * MINUS       , expr-lxor    expr-shift, expr-lxor-p,
 * PLUS        , expr-lxor    expr-shift, expr-lxor-p,
 * OP          , expr-lxor    expr-shift, expr-lxor-p,
 * OS          , expr-lxor    expr-shift, expr-lxor-p,
 * OC          , expr-lxor    expr-shift, expr-lxor-p,
 * NAME        , expr-lxor    expr-shift, expr-lxor-p,
 * NUMBER      , expr-lxor    expr-shift, expr-lxor-p,
 * STRING      , expr-lxor    expr-shift, expr-lxor-p,
 * LXOR        , expr-lxor-p  LXOR, ACTION_122, expr-shift, ACTION_125, expr-lxor-p,
 * LAND        , expr-lxor-p ()
 * LOR         , expr-lxor-p ()
 * CMPOP       , expr-lxor-p ()
 * IN          , expr-lxor-p ()
 * IS          , expr-lxor-p ()
 * AND         , expr-lxor-p ()
 * OR          , expr-lxor-p ()
 * SEMI        , expr-lxor-p ()
 * NL          , expr-lxor-p ()
 * ASSIGN      , expr-lxor-p ()
 * CS          , expr-lxor-p ()
 * CP          , expr-lxor-p ()
 * COLON       , expr-lxor-p ()
 * COMMA       , expr-lxor-p ()
 * CC          , expr-lxor-p ()
 * LNOT        , expr-shift   expr-add, expr-shift-p,
 * MINUS       , expr-shift   expr-add, expr-shift-p,
 * PLUS        , expr-shift   expr-add, expr-shift-p,
 * OP          , expr-shift   expr-add, expr-shift-p,
 * OS          , expr-shift   expr-add, expr-shift-p,
 * OC          , expr-shift   expr-add, expr-shift-p,
 * NAME        , expr-shift   expr-add, expr-shift-p,
 * NUMBER      , expr-shift   expr-add, expr-shift-p,
 * STRING      , expr-shift   expr-add, expr-shift-p,
 * SHIFT       , expr-shift-p SHIFT, ACTION_122, expr-add, ACTION_125, expr-shift-p,
 * LXOR        , expr-shift-p()
 * LAND        , expr-shift-p()
 * LOR         , expr-shift-p()
 * CMPOP       , expr-shift-p()
 * IN          , expr-shift-p()
 * IS          , expr-shift-p()
 * AND         , expr-shift-p()
 * OR          , expr-shift-p()
 * SEMI        , expr-shift-p()
 * NL          , expr-shift-p()
 * ASSIGN      , expr-shift-p()
 * CS          , expr-shift-p()
 * CP          , expr-shift-p()
 * COLON       , expr-shift-p()
 * COMMA       , expr-shift-p()
 * CC          , expr-shift-p()
 * LNOT        , expr-add     expr-mul, expr-add-p,
 * MINUS       , expr-add     expr-mul, expr-add-p,
 * PLUS        , expr-add     expr-mul, expr-add-p,
 * OP          , expr-add     expr-mul, expr-add-p,
 * OS          , expr-add     expr-mul, expr-add-p,
 * OC          , expr-add     expr-mul, expr-add-p,
 * NAME        , expr-add     expr-mul, expr-add-p,
 * NUMBER      , expr-add     expr-mul, expr-add-p,
 * STRING      , expr-add     expr-mul, expr-add-p,
 * PLUS        , expr-add-p   PLUS, ACTION_122, expr-mul, ACTION_125, expr-add-p,
 * MINUS       , expr-add-p   MINUS, ACTION_122, expr-mul, ACTION_125, expr-add-p,
 * SHIFT       , expr-add-p  ()
 * LXOR        , expr-add-p  ()
 * LAND        , expr-add-p  ()
 * LOR         , expr-add-p  ()
 * CMPOP       , expr-add-p  ()
 * IN          , expr-add-p  ()
 * IS          , expr-add-p  ()
 * AND         , expr-add-p  ()
 * OR          , expr-add-p  ()
 * SEMI        , expr-add-p  ()
 * NL          , expr-add-p  ()
 * ASSIGN      , expr-add-p  ()
 * CS          , expr-add-p  ()
 * CP          , expr-add-p  ()
 * COLON       , expr-add-p  ()
 * COMMA       , expr-add-p  ()
 * CC          , expr-add-p  ()
 * LNOT        , expr-mul     expr-unary, expr-mul-p,
 * MINUS       , expr-mul     expr-unary, expr-mul-p,
 * PLUS        , expr-mul     expr-unary, expr-mul-p,
 * OP          , expr-mul     expr-unary, expr-mul-p,
 * OS          , expr-mul     expr-unary, expr-mul-p,
 * OC          , expr-mul     expr-unary, expr-mul-p,
 * NAME        , expr-mul     expr-unary, expr-mul-p,
 * NUMBER      , expr-mul     expr-unary, expr-mul-p,
 * STRING      , expr-mul     expr-unary, expr-mul-p,
 * MULOP       , expr-mul-p   MULOP, ACTION_122, expr-unary, ACTION_125, expr-mul-p,
 * PLUS        , expr-mul-p  ()
 * MINUS       , expr-mul-p  ()
 * SHIFT       , expr-mul-p  ()
 * LXOR        , expr-mul-p  ()
 * LAND        , expr-mul-p  ()
 * LOR         , expr-mul-p  ()
 * CMPOP       , expr-mul-p  ()
 * IN          , expr-mul-p  ()
 * IS          , expr-mul-p  ()
 * AND         , expr-mul-p  ()
 * OR          , expr-mul-p  ()
 * SEMI        , expr-mul-p  ()
 * NL          , expr-mul-p  ()
 * ASSIGN      , expr-mul-p  ()
 * CS          , expr-mul-p  ()
 * CP          , expr-mul-p  ()
 * COLON       , expr-mul-p  ()
 * COMMA       , expr-mul-p  ()
 * CC          , expr-mul-p  ()
 * LNOT        , expr-unary   LNOT, ACTION_120, expr-unary, ACTION_123,
 * MINUS       , expr-unary   MINUS, ACTION_131, expr-unary, ACTION_123,
 * PLUS        , expr-unary   PLUS, expr-unary,
 * OP          , expr-unary   expr-pow,
 * OS          , expr-unary   expr-pow,
 * OC          , expr-unary   expr-pow,
 * NAME        , expr-unary   expr-pow,
 * NUMBER      , expr-unary   expr-pow,
 * STRING      , expr-unary   expr-pow,
 * OP          , expr-pow     expr-array, expr-pow-p,
 * OS          , expr-pow     expr-array, expr-pow-p,
 * OC          , expr-pow     expr-array, expr-pow-p,
 * NAME        , expr-pow     expr-array, expr-pow-p,
 * NUMBER      , expr-pow     expr-array, expr-pow-p,
 * STRING      , expr-pow     expr-array, expr-pow-p,
 * POW         , expr-pow-p   POW, ACTION_122, expr-array, expr-pow-p, ACTION_125,
 * MULOP       , expr-pow-p  ()
 * PLUS        , expr-pow-p  ()
 * MINUS       , expr-pow-p  ()
 * SHIFT       , expr-pow-p  ()
 * LXOR        , expr-pow-p  ()
 * LAND        , expr-pow-p  ()
 * LOR         , expr-pow-p  ()
 * CMPOP       , expr-pow-p  ()
 * IN          , expr-pow-p  ()
 * IS          , expr-pow-p  ()
 * AND         , expr-pow-p  ()
 * OR          , expr-pow-p  ()
 * SEMI        , expr-pow-p  ()
 * NL          , expr-pow-p  ()
 * ASSIGN      , expr-pow-p  ()
 * CS          , expr-pow-p  ()
 * CP          , expr-pow-p  ()
 * COLON       , expr-pow-p  ()
 * COMMA       , expr-pow-p  ()
 * CC          , expr-pow-p  ()
 * OP          , expr-array   expr-prim, expr-array-p,
 * OS          , expr-array   expr-prim, expr-array-p,
 * OC          , expr-array   expr-prim, expr-array-p,
 * NAME        , expr-array   expr-prim, expr-array-p,
 * NUMBER      , expr-array   expr-prim, expr-array-p,
 * STRING      , expr-array   expr-prim, expr-array-p,
 * OS          , expr-array-p OS, ACTION_140, array-index, CS, ACTION_181, expr-array-p,
 * OP          , expr-array-p OP, ACTION_140, opt-actuals, CP, ACTION_154, expr-array-p,
 * POW         , expr-array-p()
 * MULOP       , expr-array-p()
 * PLUS        , expr-array-p()
 * MINUS       , expr-array-p()
 * SHIFT       , expr-array-p()
 * LXOR        , expr-array-p()
 * LAND        , expr-array-p()
 * LOR         , expr-array-p()
 * CMPOP       , expr-array-p()
 * IN          , expr-array-p()
 * IS          , expr-array-p()
 * AND         , expr-array-p()
 * OR          , expr-array-p()
 * SEMI        , expr-array-p()
 * NL          , expr-array-p()
 * ASSIGN      , expr-array-p()
 * CS          , expr-array-p()
 * CP          , expr-array-p()
 * COLON       , expr-array-p()
 * COMMA       , expr-array-p()
 * CC          , expr-array-p()
 * LNOT        , array-index  expr, opt-slice,
 * MINUS       , array-index  expr, opt-slice,
 * PLUS        , array-index  expr, opt-slice,
 * OP          , array-index  expr, opt-slice,
 * OS          , array-index  expr, opt-slice,
 * OC          , array-index  expr, opt-slice,
 * NAME        , array-index  expr, opt-slice,
 * NUMBER      , array-index  expr, opt-slice,
 * STRING      , array-index  expr, opt-slice,
 * NOT         , array-index  expr, opt-slice,
 * COLON       , array-index  ACTION_129, slice,
 * COLON       , opt-slice    ACTION_128, slice,
 * CS          , opt-slice    ACTION_129,
 * COLON       , slice        COLON, opt-expr, slice-p, ACTION_128,
 * COLON       , slice-p      COLON, opt-expr,
 * CS          , slice-p      ACTION_129,
 * LNOT        , opt-expr     ACTION_156, expr,
 * MINUS       , opt-expr     ACTION_156, expr,
 * PLUS        , opt-expr     ACTION_156, expr,
 * OP          , opt-expr     ACTION_156, expr,
 * OS          , opt-expr     ACTION_156, expr,
 * OC          , opt-expr     ACTION_156, expr,
 * NAME        , opt-expr     ACTION_156, expr,
 * NUMBER      , opt-expr     ACTION_156, expr,
 * STRING      , opt-expr     ACTION_156, expr,
 * NOT         , opt-expr     ACTION_156, expr,
 * COLON       , opt-expr     ACTION_129,
 * CS          , opt-expr     ACTION_129,
 * OP          , expr-prim    OP, opt-tuple, CP, ACTION_171,
 * OS          , expr-prim    OS, opt-actuals, CS, ACTION_170,
 * OC          , expr-prim    OC, ACTION_127, opt-dict-ents, CC, ACTION_158,
 * NAME        , expr-prim    NAME, ACTION_150,
 * NUMBER      , expr-prim    NUMBER, ACTION_141,
 * STRING      , expr-prim    STRING, ACTION_142, strings-p,
 * STRING      , strings-p    STRING, ACTION_168, strings-p,
 * OS          , strings-p   ()
 * OP          , strings-p   ()
 * POW         , strings-p   ()
 * MULOP       , strings-p   ()
 * PLUS        , strings-p   ()
 * MINUS       , strings-p   ()
 * SHIFT       , strings-p   ()
 * LXOR        , strings-p   ()
 * LAND        , strings-p   ()
 * LOR         , strings-p   ()
 * CMPOP       , strings-p   ()
 * IN          , strings-p   ()
 * IS          , strings-p   ()
 * AND         , strings-p   ()
 * OR          , strings-p   ()
 * SEMI        , strings-p   ()
 * NL          , strings-p   ()
 * ASSIGN      , strings-p   ()
 * CS          , strings-p   ()
 * CP          , strings-p   ()
 * COLON       , strings-p   ()
 * COMMA       , strings-p   ()
 * CC          , strings-p   ()
 * LNOT        , opt-tuple    expr, opt-tuple-p,
 * MINUS       , opt-tuple    expr, opt-tuple-p,
 * PLUS        , opt-tuple    expr, opt-tuple-p,
 * OP          , opt-tuple    expr, opt-tuple-p,
 * OS          , opt-tuple    expr, opt-tuple-p,
 * OC          , opt-tuple    expr, opt-tuple-p,
 * NAME        , opt-tuple    expr, opt-tuple-p,
 * NUMBER      , opt-tuple    expr, opt-tuple-p,
 * STRING      , opt-tuple    expr, opt-tuple-p,
 * NOT         , opt-tuple    expr, opt-tuple-p,
 * CP          , opt-tuple    ACTION_143,
 * COMMA       , opt-tuple-p  COMMA, ACTION_140, opt-actuals, ACTION_173,
 * CP          , opt-tuple-p  ACTION_129,
 * LNOT        , opt-actuals  actuals,
 * MINUS       , opt-actuals  actuals,
 * PLUS        , opt-actuals  actuals,
 * OP          , opt-actuals  actuals,
 * OS          , opt-actuals  actuals,
 * OC          , opt-actuals  actuals,
 * NAME        , opt-actuals  actuals,
 * NUMBER      , opt-actuals  actuals,
 * STRING      , opt-actuals  actuals,
 * NOT         , opt-actuals  actuals,
 * CS          , opt-actuals  ACTION_127,
 * CP          , opt-actuals  ACTION_127,
 * LNOT        , actuals      ACTION_127, expr, actual-p, actuals-p,
 * MINUS       , actuals      ACTION_127, expr, actual-p, actuals-p,
 * PLUS        , actuals      ACTION_127, expr, actual-p, actuals-p,
 * OP          , actuals      ACTION_127, expr, actual-p, actuals-p,
 * OS          , actuals      ACTION_127, expr, actual-p, actuals-p,
 * OC          , actuals      ACTION_127, expr, actual-p, actuals-p,
 * NAME        , actuals      ACTION_127, expr, actual-p, actuals-p,
 * NUMBER      , actuals      ACTION_127, expr, actual-p, actuals-p,
 * STRING      , actuals      ACTION_127, expr, actual-p, actuals-p,
 * NOT         , actuals      ACTION_127, expr, actual-p, actuals-p,
 * ASSIGN      , actual-p     ASSIGN, ACTION_182, expr, ACTION_162,
 * COMMA       , actual-p     ACTION_176,
 * CS          , actual-p     ACTION_176,
 * CP          , actual-p     ACTION_176,
 * COMMA       , actuals-p    COMMA, expr, actual-p, actuals-p,
 * CS          , actuals-p   ()
 * CP          , actuals-p   ()
 * LNOT        , opt-dict-ents dict-ent, dict-ents-p,
 * MINUS       , opt-dict-ents dict-ent, dict-ents-p,
 * PLUS        , opt-dict-ents dict-ent, dict-ents-p,
 * OP          , opt-dict-ents dict-ent, dict-ents-p,
 * OS          , opt-dict-ents dict-ent, dict-ents-p,
 * OC          , opt-dict-ents dict-ent, dict-ents-p,
 * NAME        , opt-dict-ents dict-ent, dict-ents-p,
 * NUMBER      , opt-dict-ents dict-ent, dict-ents-p,
 * STRING      , opt-dict-ents dict-ent, dict-ents-p,
 * NOT         , opt-dict-ents dict-ent, dict-ents-p,
 * CC          , opt-dict-ents()
 * COMMA       , dict-ents-p  COMMA, dict-ent, dict-ents-p,
 * CC          , dict-ents-p ()
 * LNOT        , dict-ent     expr, ACTION_159, dict-ent-p,
 * MINUS       , dict-ent     expr, ACTION_159, dict-ent-p,
 * PLUS        , dict-ent     expr, ACTION_159, dict-ent-p,
 * OP          , dict-ent     expr, ACTION_159, dict-ent-p,
 * OS          , dict-ent     expr, ACTION_159, dict-ent-p,
 * OC          , dict-ent     expr, ACTION_159, dict-ent-p,
 * NAME        , dict-ent     expr, ACTION_159, dict-ent-p,
 * NUMBER      , dict-ent     expr, ACTION_159, dict-ent-p,
 * STRING      , dict-ent     expr, ACTION_159, dict-ent-p,
 * NOT         , dict-ent     expr, ACTION_159, dict-ent-p,
 * COLON       , dict-ent-p   COLON, expr, ACTION_159,
 */
static const token_t PARSE_TABLE_DECLARATION(production_table)[] = {
    /*    0 */    NON_TERMINAL_start, NON_TERMINAL_start, ACTION_130, NON_TERMINAL_command, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*    8 */    NON_TERMINAL_start, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   12 */    NON_TERMINAL_command, ACTION_179, NON_TERMINAL_stat, ACTION_136, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   20 */    NON_TERMINAL_command, ACTION_183, NON_TERMINAL_suite, COLON, CP, NON_TERMINAL_opt_formals, OP, ACTION_133, NAME, ACTION_146, DEF, TOKEN_NONE,
    /*   32 */    NON_TERMINAL_command, NAME, IMPORT, TOKEN_NONE,
    /*   36 */    NON_TERMINAL_opt_formals, NON_TERMINAL_formals, TOKEN_NONE, TOKEN_NONE,
    /*   40 */    NON_TERMINAL_opt_formals, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   44 */    NON_TERMINAL_formals, NON_TERMINAL_formals_p, NON_TERMINAL_formal, TOKEN_NONE,
    /*   48 */    NON_TERMINAL_formals_p, NON_TERMINAL_formals_p, NON_TERMINAL_formal, COMMA, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   56 */    NON_TERMINAL_formals_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   60 */    NON_TERMINAL_formal, NON_TERMINAL_opt_named_p, ACTION_155, NAME, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   68 */    NON_TERMINAL_opt_named_p, ACTION_165, NON_TERMINAL_expr, ASSIGN, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   76 */    NON_TERMINAL_opt_named_p, ACTION_149, TOKEN_NONE, TOKEN_NONE,
    /*   80 */    NON_TERMINAL_opt_stats, NON_TERMINAL_opt_stats, NON_TERMINAL_stat, TOKEN_NONE,
    /*   84 */    NON_TERMINAL_opt_stats, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*   88 */    NON_TERMINAL_stat, NON_TERMINAL_simple_stat, TOKEN_NONE, TOKEN_NONE,
    /*   92 */    NON_TERMINAL_stat, NON_TERMINAL_compound_stat, ACTION_157, TOKEN_NONE,
    /*   96 */    NON_TERMINAL_stat, NL, TOKEN_NONE, TOKEN_NONE,
    /*  100 */    NON_TERMINAL_simple_stat, NL, NON_TERMINAL_small_stats_p, NON_TERMINAL_small_stat, ACTION_151, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  108 */    NON_TERMINAL_small_stats_p, NON_TERMINAL_small_stats_p, NON_TERMINAL_small_stat, SEMI, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  116 */    NON_TERMINAL_small_stats_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  120 */    NON_TERMINAL_small_stat, NON_TERMINAL_assign_expr, TOKEN_NONE, TOKEN_NONE,
    /*  124 */    NON_TERMINAL_small_stat, ACTION_134, NON_TERMINAL_ret_expr, RETURN, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  132 */    NON_TERMINAL_small_stat, ACTION_139, BREAK, TOKEN_NONE,
    /*  136 */    NON_TERMINAL_small_stat, ACTION_144, CONTINUE, TOKEN_NONE,
    /*  140 */    NON_TERMINAL_small_stat, PASS, TOKEN_NONE, TOKEN_NONE,
    /*  144 */    NON_TERMINAL_small_stat, NON_TERMINAL_globals, GLOBAL, TOKEN_NONE,
    /*  148 */    NON_TERMINAL_small_stat, NON_TERMINAL_dels_p, NON_TERMINAL_del, DEL, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  156 */    NON_TERMINAL_small_stat, ACTION_135, NON_TERMINAL_expr, ASSERT, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  164 */    NON_TERMINAL_dels_p, NON_TERMINAL_dels_p, NON_TERMINAL_del, COMMA, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  172 */    NON_TERMINAL_dels_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  176 */    NON_TERMINAL_del, ACTION_126, ACTION_152, NON_TERMINAL_expr_array, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  184 */    NON_TERMINAL_ret_expr, NON_TERMINAL_expr, TOKEN_NONE, TOKEN_NONE,
    /*  188 */    NON_TERMINAL_ret_expr, ACTION_132, TOKEN_NONE, TOKEN_NONE,
    /*  192 */    NON_TERMINAL_assign_expr, NON_TERMINAL_assign_expr_p, NON_TERMINAL_expr, TOKEN_NONE,
    /*  196 */    NON_TERMINAL_assign_expr_p, ACTION_167, NON_TERMINAL_expr, ACTION_185, ASSIGN, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  204 */    NON_TERMINAL_assign_expr_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  208 */    NON_TERMINAL_globals, NON_TERMINAL_globals_p, NON_TERMINAL_global, TOKEN_NONE,
    /*  212 */    NON_TERMINAL_globals, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  216 */    NON_TERMINAL_globals_p, NON_TERMINAL_globals_p, NON_TERMINAL_global, COMMA, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  224 */    NON_TERMINAL_globals_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  228 */    NON_TERMINAL_global, ACTION_153, NAME, TOKEN_NONE,
    /*  232 */    NON_TERMINAL_compound_stat, NON_TERMINAL_if_stat, TOKEN_NONE, TOKEN_NONE,
    /*  236 */    NON_TERMINAL_compound_stat, NON_TERMINAL_while_stat, TOKEN_NONE, TOKEN_NONE,
    /*  240 */    NON_TERMINAL_compound_stat, NON_TERMINAL_for_stat, TOKEN_NONE, TOKEN_NONE,
    /*  244 */    NON_TERMINAL_if_stat, ACTION_177, NON_TERMINAL_elif_stats, NON_TERMINAL_suite, NON_TERMINAL_if_expr, IF, TOKEN_NONE, TOKEN_NONE,
    /*  252 */    NON_TERMINAL_elif_stats, ACTION_175, NON_TERMINAL_elif_stats, NON_TERMINAL_suite, NON_TERMINAL_if_expr, ACTION_174, ELIF, TOKEN_NONE,
    /*  260 */    NON_TERMINAL_elif_stats, NON_TERMINAL_suite, ACTION_121, COLON, ELSE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  268 */    NON_TERMINAL_elif_stats, ACTION_137, TOKEN_NONE, TOKEN_NONE,
    /*  272 */    NON_TERMINAL_if_expr, ACTION_161, COLON, NON_TERMINAL_expr, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  280 */    NON_TERMINAL_while_stat, ACTION_184, NON_TERMINAL_while_else_stat, ACTION_169, NON_TERMINAL_suite, ACTION_161, COLON, NON_TERMINAL_expr, WHILE, ACTION_137, TOKEN_NONE, TOKEN_NONE,
    /*  292 */    NON_TERMINAL_while_else_stat, NON_TERMINAL_suite, COLON, ELSE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  300 */    NON_TERMINAL_while_else_stat, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  304 */    NON_TERMINAL_for_stat, ACTION_119, NON_TERMINAL_while_else_stat, ACTION_172, NON_TERMINAL_suite, NON_TERMINAL_for_params, IN, ACTION_133, NAME, FOR, TOKEN_NONE, TOKEN_NONE,
    /*  316 */    NON_TERMINAL_for_params, ACTION_180, COLON, CP, NON_TERMINAL_opt_actuals, OP, RANGE, TOKEN_NONE,
    /*  324 */    NON_TERMINAL_for_params, ACTION_163, COLON, NON_TERMINAL_expr, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  332 */    NON_TERMINAL_suite, NON_TERMINAL_simple_stat, TOKEN_NONE, TOKEN_NONE,
    /*  336 */    NON_TERMINAL_suite, ACTION_178, EXDENT, NON_TERMINAL_opt_stats, NON_TERMINAL_stat, ACTION_138, INDENT, NL, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  348 */    NON_TERMINAL_expr, NON_TERMINAL_expr_or_p, NON_TERMINAL_expr_and, TOKEN_NONE,
    /*  352 */    NON_TERMINAL_expr_or_p, NON_TERMINAL_expr_or_p, ACTION_166, NON_TERMINAL_expr_and, ACTION_160, OR, TOKEN_NONE, TOKEN_NONE,
    /*  360 */    NON_TERMINAL_expr_or_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  364 */    NON_TERMINAL_expr_and, NON_TERMINAL_expr_and_p, NON_TERMINAL_expr_not, TOKEN_NONE,
    /*  368 */    NON_TERMINAL_expr_and_p, NON_TERMINAL_expr_and_p, ACTION_124, NON_TERMINAL_expr_not, ACTION_161, AND, TOKEN_NONE, TOKEN_NONE,
    /*  376 */    NON_TERMINAL_expr_and_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  380 */    NON_TERMINAL_expr_not, NON_TERMINAL_expr_cmp, TOKEN_NONE, TOKEN_NONE,
    /*  384 */    NON_TERMINAL_expr_not, ACTION_147, NON_TERMINAL_expr_not, ACTION_145, NOT, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  392 */    NON_TERMINAL_expr_cmp, NON_TERMINAL_expr_cmp_p, NON_TERMINAL_expr_lor, TOKEN_NONE,
    /*  396 */    NON_TERMINAL_expr_cmp_p, NON_TERMINAL_expr_cmp_p, ACTION_148, NON_TERMINAL_expr_lor, ACTION_164, NON_TERMINAL_cmpop, TOKEN_NONE, TOKEN_NONE,
    /*  404 */    NON_TERMINAL_expr_cmp_p, NON_TERMINAL_expr_cmp_p, ACTION_125, NON_TERMINAL_expr_lor, ACTION_122, IS, TOKEN_NONE, TOKEN_NONE,
    /*  412 */    NON_TERMINAL_expr_cmp_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  416 */    NON_TERMINAL_cmpop, CMPOP, TOKEN_NONE, TOKEN_NONE,
    /*  420 */    NON_TERMINAL_cmpop, IN, TOKEN_NONE, TOKEN_NONE,
    /*  424 */    NON_TERMINAL_expr_lor, NON_TERMINAL_expr_lor_p, NON_TERMINAL_expr_land, TOKEN_NONE,
    /*  428 */    NON_TERMINAL_expr_lor_p, NON_TERMINAL_expr_lor_p, ACTION_125, NON_TERMINAL_expr_land, ACTION_122, LOR, TOKEN_NONE, TOKEN_NONE,
    /*  436 */    NON_TERMINAL_expr_lor_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  440 */    NON_TERMINAL_expr_land, NON_TERMINAL_expr_land_p, NON_TERMINAL_expr_lxor, TOKEN_NONE,
    /*  444 */    NON_TERMINAL_expr_land_p, NON_TERMINAL_expr_land_p, ACTION_125, NON_TERMINAL_expr_lxor, ACTION_122, LAND, TOKEN_NONE, TOKEN_NONE,
    /*  452 */    NON_TERMINAL_expr_land_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  456 */    NON_TERMINAL_expr_lxor, NON_TERMINAL_expr_lxor_p, NON_TERMINAL_expr_shift, TOKEN_NONE,
    /*  460 */    NON_TERMINAL_expr_lxor_p, NON_TERMINAL_expr_lxor_p, ACTION_125, NON_TERMINAL_expr_shift, ACTION_122, LXOR, TOKEN_NONE, TOKEN_NONE,
    /*  468 */    NON_TERMINAL_expr_lxor_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  472 */    NON_TERMINAL_expr_shift, NON_TERMINAL_expr_shift_p, NON_TERMINAL_expr_add, TOKEN_NONE,
    /*  476 */    NON_TERMINAL_expr_shift_p, NON_TERMINAL_expr_shift_p, ACTION_125, NON_TERMINAL_expr_add, ACTION_122, SHIFT, TOKEN_NONE, TOKEN_NONE,
    /*  484 */    NON_TERMINAL_expr_shift_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  488 */    NON_TERMINAL_expr_add, NON_TERMINAL_expr_add_p, NON_TERMINAL_expr_mul, TOKEN_NONE,
    /*  492 */    NON_TERMINAL_expr_add_p, NON_TERMINAL_expr_add_p, ACTION_125, NON_TERMINAL_expr_mul, ACTION_122, PLUS, TOKEN_NONE, TOKEN_NONE,
    /*  500 */    NON_TERMINAL_expr_add_p, NON_TERMINAL_expr_add_p, ACTION_125, NON_TERMINAL_expr_mul, ACTION_122, MINUS, TOKEN_NONE, TOKEN_NONE,
    /*  508 */    NON_TERMINAL_expr_add_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  512 */    NON_TERMINAL_expr_mul, NON_TERMINAL_expr_mul_p, NON_TERMINAL_expr_unary, TOKEN_NONE,
    /*  516 */    NON_TERMINAL_expr_mul_p, NON_TERMINAL_expr_mul_p, ACTION_125, NON_TERMINAL_expr_unary, ACTION_122, MULOP, TOKEN_NONE, TOKEN_NONE,
    /*  524 */    NON_TERMINAL_expr_mul_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  528 */    NON_TERMINAL_expr_unary, ACTION_123, NON_TERMINAL_expr_unary, ACTION_120, LNOT, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  536 */    NON_TERMINAL_expr_unary, ACTION_123, NON_TERMINAL_expr_unary, ACTION_131, MINUS, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  544 */    NON_TERMINAL_expr_unary, NON_TERMINAL_expr_unary, PLUS, TOKEN_NONE,
    /*  548 */    NON_TERMINAL_expr_unary, NON_TERMINAL_expr_pow, TOKEN_NONE, TOKEN_NONE,
    /*  552 */    NON_TERMINAL_expr_pow, NON_TERMINAL_expr_pow_p, NON_TERMINAL_expr_array, TOKEN_NONE,
    /*  556 */    NON_TERMINAL_expr_pow_p, ACTION_125, NON_TERMINAL_expr_pow_p, NON_TERMINAL_expr_array, ACTION_122, POW, TOKEN_NONE, TOKEN_NONE,
    /*  564 */    NON_TERMINAL_expr_pow_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  568 */    NON_TERMINAL_expr_array, NON_TERMINAL_expr_array_p, NON_TERMINAL_expr_prim, TOKEN_NONE,
    /*  572 */    NON_TERMINAL_expr_array_p, NON_TERMINAL_expr_array_p, ACTION_181, CS, NON_TERMINAL_array_index, ACTION_140, OS, TOKEN_NONE,
    /*  580 */    NON_TERMINAL_expr_array_p, NON_TERMINAL_expr_array_p, ACTION_154, CP, NON_TERMINAL_opt_actuals, ACTION_140, OP, TOKEN_NONE,
    /*  588 */    NON_TERMINAL_expr_array_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  592 */    NON_TERMINAL_array_index, NON_TERMINAL_opt_slice, NON_TERMINAL_expr, TOKEN_NONE,
    /*  596 */    NON_TERMINAL_array_index, NON_TERMINAL_slice, ACTION_129, TOKEN_NONE,
    /*  600 */    NON_TERMINAL_opt_slice, NON_TERMINAL_slice, ACTION_128, TOKEN_NONE,
    /*  604 */    NON_TERMINAL_opt_slice, ACTION_129, TOKEN_NONE, TOKEN_NONE,
    /*  608 */    NON_TERMINAL_slice, ACTION_128, NON_TERMINAL_slice_p, NON_TERMINAL_opt_expr, COLON, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  616 */    NON_TERMINAL_slice_p, NON_TERMINAL_opt_expr, COLON, TOKEN_NONE,
    /*  620 */    NON_TERMINAL_slice_p, ACTION_129, TOKEN_NONE, TOKEN_NONE,
    /*  624 */    NON_TERMINAL_opt_expr, NON_TERMINAL_expr, ACTION_156, TOKEN_NONE,
    /*  628 */    NON_TERMINAL_opt_expr, ACTION_129, TOKEN_NONE, TOKEN_NONE,
    /*  632 */    NON_TERMINAL_expr_prim, ACTION_171, CP, NON_TERMINAL_opt_tuple, OP, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  640 */    NON_TERMINAL_expr_prim, ACTION_170, CS, NON_TERMINAL_opt_actuals, OS, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  648 */    NON_TERMINAL_expr_prim, ACTION_158, CC, NON_TERMINAL_opt_dict_ents, ACTION_127, OC, TOKEN_NONE, TOKEN_NONE,
    /*  656 */    NON_TERMINAL_expr_prim, ACTION_150, NAME, TOKEN_NONE,
    /*  660 */    NON_TERMINAL_expr_prim, ACTION_141, NUMBER, TOKEN_NONE,
    /*  664 */    NON_TERMINAL_expr_prim, NON_TERMINAL_strings_p, ACTION_142, STRING, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  672 */    NON_TERMINAL_strings_p, NON_TERMINAL_strings_p, ACTION_168, STRING, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  680 */    NON_TERMINAL_strings_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  684 */    NON_TERMINAL_opt_tuple, NON_TERMINAL_opt_tuple_p, NON_TERMINAL_expr, TOKEN_NONE,
    /*  688 */    NON_TERMINAL_opt_tuple, ACTION_143, TOKEN_NONE, TOKEN_NONE,
    /*  692 */    NON_TERMINAL_opt_tuple_p, ACTION_173, NON_TERMINAL_opt_actuals, ACTION_140, COMMA, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  700 */    NON_TERMINAL_opt_tuple_p, ACTION_129, TOKEN_NONE, TOKEN_NONE,
    /*  704 */    NON_TERMINAL_opt_actuals, NON_TERMINAL_actuals, TOKEN_NONE, TOKEN_NONE,
    /*  708 */    NON_TERMINAL_opt_actuals, ACTION_127, TOKEN_NONE, TOKEN_NONE,
    /*  712 */    NON_TERMINAL_actuals, NON_TERMINAL_actuals_p, NON_TERMINAL_actual_p, NON_TERMINAL_expr, ACTION_127, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  720 */    NON_TERMINAL_actual_p, ACTION_162, NON_TERMINAL_expr, ACTION_182, ASSIGN, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  728 */    NON_TERMINAL_actual_p, ACTION_176, TOKEN_NONE, TOKEN_NONE,
    /*  732 */    NON_TERMINAL_actuals_p, NON_TERMINAL_actuals_p, NON_TERMINAL_actual_p, NON_TERMINAL_expr, COMMA, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  740 */    NON_TERMINAL_actuals_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  744 */    NON_TERMINAL_opt_dict_ents, NON_TERMINAL_dict_ents_p, NON_TERMINAL_dict_ent, TOKEN_NONE,
    /*  748 */    NON_TERMINAL_opt_dict_ents, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  752 */    NON_TERMINAL_dict_ents_p, NON_TERMINAL_dict_ents_p, NON_TERMINAL_dict_ent, COMMA, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  760 */    NON_TERMINAL_dict_ents_p, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  764 */    NON_TERMINAL_dict_ent, NON_TERMINAL_dict_ent_p, ACTION_159, NON_TERMINAL_expr, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
    /*  772 */    NON_TERMINAL_dict_ent_p, ACTION_159, NON_TERMINAL_expr, COLON, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE, TOKEN_NONE,
};
typedef uint8_t token_key_t;
#define production_index(i) ((i) << 2)
typedef struct { token_t token; uint8_t index; } __attribute__((packed)) parse_table_t;
/*
 * Possible graph edges 536304170994494729323230001223241302016000000000000 total 128 minimal
 */
#define non_terminal_index(i) ((i) << 1)
static const uint8_t PARSE_TABLE_DECLARATION(non_terminal_table)[] = {
    /* 0: (END DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR EXDENT NOT PLUS MINUS LNOT OS OC NUMBER STRING) */
         67,     /*         elif-stats: ACTION_137 */
         75,     /*    while-else-stat: */
      0xff,
    0xff,

    /* 4: (END) */
          2,     /*              start: */
      0xfe,   0, /* END DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR EXDENT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 8: (DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING) */
          0,     /*              start: command ACTION_130 start */
      0xfe,   0, /* END DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR EXDENT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 12: (DEF) */
          5,     /*            command: DEF ACTION_146 NAME ACTION_133 OP opt-formals CP COLON suite ACTION_183 */
      0xfe,   4, /* DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 16: (NAME OP NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING) */
          3,     /*            command: ACTION_136 stat ACTION_179 */
         20,     /*          opt-stats: stat opt-stats */
      0xfe,   4, /* DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING */

    /* 20: (NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING) */
         22,     /*               stat: simple-stat */
         25,     /*        simple-stat: ACTION_151 small-stat small-stats-p NL */
         83,     /*              suite: simple-stat */
      0xfe,   8, /* NAME OP NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 26: (NAME OP NOT PLUS MINUS LNOT OS OC NUMBER STRING) */
         30,     /*         small-stat: assign-expr */
         46,     /*           ret-expr: expr */
         48,     /*        assign-expr: expr assign-expr-p */
         68,     /*            if-expr: expr COLON ACTION_161 */
         81,     /*         for-params: expr COLON ACTION_163 */
         87,     /*               expr: expr-and expr-or-p */
         91,     /*           expr-and: expr-not expr-and-p */
        148,     /*        array-index: expr opt-slice */
        156,     /*           opt-expr: ACTION_156 expr */
        171,     /*          opt-tuple: expr opt-tuple-p */
        176,     /*        opt-actuals: actuals */
        178,     /*            actuals: ACTION_127 expr actual-p actuals-p */
        186,     /*      opt-dict-ents: dict-ent dict-ents-p */
        191,     /*           dict-ent: expr ACTION_159 dict-ent-p */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */

    /* 42: (NAME OP PLUS MINUS LNOT OS OC NUMBER STRING) */
         95,     /*           expr-not: expr-cmp */
         98,     /*           expr-cmp: expr-lor expr-cmp-p */
        106,     /*           expr-lor: expr-land expr-lor-p */
        110,     /*          expr-land: expr-lxor expr-land-p */
        114,     /*          expr-lxor: expr-shift expr-lxor-p */
        118,     /*         expr-shift: expr-add expr-shift-p */
        122,     /*           expr-add: expr-mul expr-add-p */
        128,     /*           expr-mul: expr-unary expr-mul-p */
      0xfe,  13, /* NAME OP NOT PLUS MINUS LNOT OS OC NUMBER STRING */

    /* 52: (NAME OP OS OC NUMBER STRING) */
         44,     /*                del: expr-array ACTION_152 ACTION_126 */
        137,     /*         expr-unary: expr-pow */
        138,     /*           expr-pow: expr-array expr-pow-p */
        142,     /*         expr-array: expr-prim expr-array-p */
      0xfe,  21, /* NAME OP PLUS MINUS LNOT OS OC NUMBER STRING */

    /* 58: (NAME) */
          9,     /*        opt-formals: formals */
         11,     /*            formals: formal formals-p */
         15,     /*             formal: NAME ACTION_155 opt-named-p */
         52,     /*            globals: global globals-p */
         57,     /*             global: NAME ACTION_153 */
        164,     /*          expr-prim: NAME ACTION_150 */
      0xfe,  26, /* NAME OP OS OC NUMBER STRING */

    /* 66: (OP) */
        145,     /*       expr-array-p: OP ACTION_140 opt-actuals CP ACTION_154 expr-array-p */
        158,     /*          expr-prim: OP opt-tuple CP ACTION_171 */
        170,     /*          strings-p: */
      0xfe,  26, /* NAME OP OS OC NUMBER STRING */
    0xff,

    /* 72: (OP CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP POW OS CS CC) */
        170,     /*          strings-p: */
      0xff,

    /* 74: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP POW CS CC) */
        147,     /*       expr-array-p: */
      0xfe,  36, /* OP CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP POW OS CS CC */
    0xff,

    /* 78: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP CS CC) */
        141,     /*         expr-pow-p: */
      0xfe,  37, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP POW CS CC */
    0xff,

    /* 82: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS CS CC) */
        131,     /*         expr-mul-p: */
      0xfe,  39, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP CS CC */
    0xff,

    /* 86: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT CS CC) */
        127,     /*         expr-add-p: */
      0xfe,  41, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS CS CC */
    0xff,

    /* 90: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR CS CC) */
        121,     /*       expr-shift-p: */
      0xfe,  43, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT CS CC */
    0xff,

    /* 94: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND CS CC) */
        117,     /*        expr-lxor-p: */
      0xfe,  45, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR CS CC */
    0xff,

    /* 98: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR CS CC) */
        113,     /*        expr-land-p: */
      0xfe,  47, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND CS CC */
    0xff,

    /* 102: (CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP CS CC) */
        109,     /*         expr-lor-p: */
      0xfe,  49, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR CS CC */
    0xff,

    /* 106: (CP COLON COMMA ASSIGN NL SEMI OR AND CS CC) */
        103,     /*         expr-cmp-p: */
      0xfe,  51, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP CS CC */
    0xff,

    /* 110: (CP COLON COMMA ASSIGN NL SEMI OR CS CC) */
         94,     /*         expr-and-p: */
      0xfe,  53, /* CP COLON COMMA ASSIGN NL SEMI OR AND CS CC */
    0xff,

    /* 114: (CP COLON COMMA ASSIGN NL SEMI CS CC) */
         90,     /*          expr-or-p: */
      0xfe,  55, /* CP COLON COMMA ASSIGN NL SEMI OR CS CC */
    0xff,

    /* 118: (CP COMMA CS) */
        182,     /*           actual-p: ACTION_176 */
      0xfe,  57, /* CP COLON COMMA ASSIGN NL SEMI CS CC */
    0xff,

    /* 122: (CP COMMA) */
         19,     /*        opt-named-p: ACTION_149 */
      0xfe,  59, /* CP COMMA CS */
    0xff,

    /* 126: (CP) */
         10,     /*        opt-formals: */
         14,     /*          formals-p: */
        172,     /*          opt-tuple: ACTION_143 */
        175,     /*        opt-tuple-p: ACTION_129 */
        177,     /*        opt-actuals: ACTION_127 */
        185,     /*          actuals-p: */
      0xfe,  61, /* CP COMMA */

    /* 134: (COLON CS) */
        157,     /*           opt-expr: ACTION_129 */
      0xfe,  57, /* CP COLON COMMA ASSIGN NL SEMI CS CC */
    0xff,

    /* 138: (COLON) */
        149,     /*        array-index: ACTION_129 slice */
        150,     /*          opt-slice: ACTION_128 slice */
        152,     /*              slice: COLON opt-expr slice-p ACTION_128 */
        154,     /*            slice-p: COLON opt-expr */
        193,     /*         dict-ent-p: COLON expr ACTION_159 */
      0xfe,  67, /* COLON CS */
    0xff,

    /* 146: (IMPORT) */
          8,     /*            command: IMPORT NAME */
      0xfe,   4, /* DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 150: (COMMA) */
         12,     /*          formals-p: COMMA formal formals-p */
         41,     /*             dels-p: COMMA del dels-p */
         54,     /*          globals-p: COMMA global globals-p */
        173,     /*        opt-tuple-p: COMMA ACTION_140 opt-actuals ACTION_173 */
        183,     /*          actuals-p: COMMA expr actual-p actuals-p */
        188,     /*        dict-ents-p: COMMA dict-ent dict-ents-p */
      0xfe,  61, /* CP COMMA */

    /* 158: (ASSIGN) */
         17,     /*        opt-named-p: ASSIGN expr ACTION_165 */
         49,     /*      assign-expr-p: ASSIGN ACTION_185 expr ACTION_167 */
        180,     /*           actual-p: ASSIGN ACTION_182 expr ACTION_162 */
      0xfe,  57, /* CP COLON COMMA ASSIGN NL SEMI CS CC */
    0xff,

    /* 164: (NL SEMI) */
         43,     /*             dels-p: */
         47,     /*           ret-expr: ACTION_132 */
         51,     /*      assign-expr-p: */
         53,     /*            globals: */
         56,     /*          globals-p: */
      0xfe,  57, /* CP COLON COMMA ASSIGN NL SEMI CS CC */
    0xff,

    /* 172: (NL) */
         24,     /*               stat: NL */
         29,     /*      small-stats-p: */
         84,     /*              suite: NL INDENT ACTION_138 stat opt-stats EXDENT ACTION_178 */
         67,     /*         elif-stats: ACTION_137 */
         75,     /*    while-else-stat: */
          0,     /*              start: command ACTION_130 start */
          3,     /*            command: ACTION_136 stat ACTION_179 */
         20,     /*          opt-stats: stat opt-stats */
      0xfe,  82, /* NL SEMI */

    /* 182: (SEMI) */
         27,     /*      small-stats-p: SEMI small-stat small-stats-p */
      0xfe,  82, /* NL SEMI */
    0xff,

    /* 186: (RETURN) */
         31,     /*         small-stat: RETURN ret-expr ACTION_134 */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 190: (BREAK) */
         33,     /*         small-stat: BREAK ACTION_139 */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 194: (CONTINUE) */
         34,     /*         small-stat: CONTINUE ACTION_144 */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 198: (PASS) */
         35,     /*         small-stat: PASS */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 202: (GLOBAL) */
         36,     /*         small-stat: GLOBAL globals */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 206: (DEL) */
         37,     /*         small-stat: DEL del dels-p */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 210: (ASSERT) */
         39,     /*         small-stat: ASSERT expr ACTION_135 */
      0xfe,  10, /* NAME OP RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 214: (IF WHILE FOR) */
         23,     /*               stat: ACTION_157 compound-stat */
      0xfe,   8, /* NAME OP NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 218: (IF) */
         58,     /*      compound-stat: if-stat */
         61,     /*            if-stat: IF if-expr suite elif-stats ACTION_177 */
      0xfe, 107, /* IF WHILE FOR */

    /* 222: (ELIF) */
         63,     /*         elif-stats: ELIF ACTION_174 if-expr suite elif-stats ACTION_175 */
      0xff,

    /* 224: (ELSE) */
         65,     /*         elif-stats: ELSE COLON ACTION_121 suite */
         73,     /*    while-else-stat: ELSE COLON suite */
      0xff,
    0xff,

    /* 228: (WHILE) */
         59,     /*      compound-stat: while-stat */
         70,     /*         while-stat: ACTION_137 WHILE expr COLON ACTION_161 suite ACTION_169 while-else-stat ACTION_184 */
      0xfe, 107, /* IF WHILE FOR */

    /* 232: (FOR) */
         60,     /*      compound-stat: for-stat */
         76,     /*           for-stat: FOR NAME ACTION_133 IN for-params suite ACTION_172 while-else-stat ACTION_119 */
      0xfe, 107, /* IF WHILE FOR */

    /* 236: (IN CMPOP) */
         99,     /*         expr-cmp-p: cmpop ACTION_164 expr-lor ACTION_148 expr-cmp-p */
      0xfe,  51, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP CS CC */
    0xff,

    /* 240: (IN) */
        105,     /*              cmpop: IN */
      0xfe, 118, /* IN CMPOP */
    0xff,

    /* 244: (RANGE) */
         79,     /*         for-params: RANGE OP opt-actuals CP COLON ACTION_180 */
      0xff,

    /* 246: (EXDENT) */
         21,     /*          opt-stats: */
      0xfe,   0, /* END DEF NAME OP IMPORT NL RETURN BREAK CONTINUE PASS GLOBAL DEL ASSERT IF WHILE FOR EXDENT NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 250: (OR) */
         88,     /*          expr-or-p: OR ACTION_160 expr-and ACTION_166 expr-or-p */
      0xfe,  55, /* CP COLON COMMA ASSIGN NL SEMI OR CS CC */
    0xff,

    /* 254: (AND) */
         92,     /*         expr-and-p: AND ACTION_161 expr-not ACTION_124 expr-and-p */
      0xfe,  53, /* CP COLON COMMA ASSIGN NL SEMI OR AND CS CC */
    0xff,

    /* 258: (NOT) */
         96,     /*           expr-not: NOT ACTION_145 expr-not ACTION_147 */
      0xfe,  13, /* NAME OP NOT PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 262: (IS) */
        101,     /*         expr-cmp-p: IS ACTION_122 expr-lor ACTION_125 expr-cmp-p */
      0xfe,  51, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP CS CC */
    0xff,

    /* 266: (CMPOP) */
        104,     /*              cmpop: CMPOP */
      0xfe, 118, /* IN CMPOP */
    0xff,

    /* 270: (LOR) */
        107,     /*         expr-lor-p: LOR ACTION_122 expr-land ACTION_125 expr-lor-p */
      0xfe,  49, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR CS CC */
    0xff,

    /* 274: (LAND) */
        111,     /*        expr-land-p: LAND ACTION_122 expr-lxor ACTION_125 expr-land-p */
      0xfe,  47, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND CS CC */
    0xff,

    /* 278: (LXOR) */
        115,     /*        expr-lxor-p: LXOR ACTION_122 expr-shift ACTION_125 expr-lxor-p */
      0xfe,  45, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR CS CC */
    0xff,

    /* 282: (SHIFT) */
        119,     /*       expr-shift-p: SHIFT ACTION_122 expr-add ACTION_125 expr-shift-p */
      0xfe,  43, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT CS CC */
    0xff,

    /* 286: (PLUS) */
        123,     /*         expr-add-p: PLUS ACTION_122 expr-mul ACTION_125 expr-add-p */
        136,     /*         expr-unary: PLUS expr-unary */
        170,     /*          strings-p: */
        131,     /*         expr-mul-p: */
        141,     /*         expr-pow-p: */
        147,     /*       expr-array-p: */
      0xfe,  21, /* NAME OP PLUS MINUS LNOT OS OC NUMBER STRING */

    /* 294: (MINUS) */
        125,     /*         expr-add-p: MINUS ACTION_122 expr-mul ACTION_125 expr-add-p */
        134,     /*         expr-unary: MINUS ACTION_131 expr-unary ACTION_123 */
        170,     /*          strings-p: */
        131,     /*         expr-mul-p: */
        141,     /*         expr-pow-p: */
        147,     /*       expr-array-p: */
      0xfe,  21, /* NAME OP PLUS MINUS LNOT OS OC NUMBER STRING */

    /* 302: (MULOP) */
        129,     /*         expr-mul-p: MULOP ACTION_122 expr-unary ACTION_125 expr-mul-p */
      0xfe,  39, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP CS CC */
    0xff,

    /* 306: (LNOT) */
        132,     /*         expr-unary: LNOT ACTION_120 expr-unary ACTION_123 */
      0xfe,  21, /* NAME OP PLUS MINUS LNOT OS OC NUMBER STRING */
    0xff,

    /* 310: (POW) */
        139,     /*         expr-pow-p: POW ACTION_122 expr-array expr-pow-p ACTION_125 */
      0xfe,  37, /* CP COLON COMMA ASSIGN NL SEMI IN OR AND IS CMPOP LOR LAND LXOR SHIFT PLUS MINUS MULOP POW CS CC */
    0xff,

    /* 314: (OS) */
        143,     /*       expr-array-p: OS ACTION_140 array-index CS ACTION_181 expr-array-p */
        160,     /*          expr-prim: OS opt-actuals CS ACTION_170 */
        170,     /*          strings-p: */
      0xfe,  26, /* NAME OP OS OC NUMBER STRING */
    0xff,

    /* 320: (CP CS) */
        177,     /*        opt-actuals: ACTION_127 */
        185,     /*          actuals-p: */
      0xfe,  59, /* CP COMMA CS */

    /* 324: (CS) */
        151,     /*          opt-slice: ACTION_129 */
        155,     /*            slice-p: ACTION_129 */
        157,     /*           opt-expr: ACTION_129 */
      0xfe, 160, /* CP CS */
    0xff,

    /* 330: (OC) */
        162,     /*          expr-prim: OC ACTION_127 opt-dict-ents CC ACTION_158 */
      0xfe,  26, /* NAME OP OS OC NUMBER STRING */
    0xff,

    /* 334: (CC) */
        187,     /*      opt-dict-ents: */
        190,     /*        dict-ents-p: */
      0xfe,  57, /* CP COLON COMMA ASSIGN NL SEMI CS CC */

    /* 338: (NUMBER) */
        165,     /*          expr-prim: NUMBER ACTION_141 */
      0xfe,  26, /* NAME OP OS OC NUMBER STRING */
    0xff,

    /* 342: (STRING) */
        166,     /*          expr-prim: STRING ACTION_142 strings-p */
        168,     /*          strings-p: STRING ACTION_168 strings-p */
      0xfe,  26, /* NAME OP OS OC NUMBER STRING */

};
#define NON_TERMINAL_SIZE 346
static const parse_table_t PARSE_TABLE_DECLARATION(terminal_table)[] = {
    { END, 2 },
    { DEF, 6 },
    { NAME, 29 },
    { OP, 33 },
    { CP, 63 },
    { COLON, 69 },
    { IMPORT, 73 },
    { COMMA, 75 },
    { ASSIGN, 79 },
    { NL, 86 },
    { SEMI, 91 },
    { RETURN, 93 },
    { BREAK, 95 },
    { CONTINUE, 97 },
    { PASS, 99 },
    { GLOBAL, 101 },
    { DEL, 103 },
    { ASSERT, 105 },
    { IF, 109 },
    { ELIF, 111 },
    { ELSE, 112 },
    { WHILE, 114 },
    { FOR, 116 },
    { IN, 120 },
    { RANGE, 122 },
    { EXDENT, 123 },
    { OR, 125 },
    { AND, 127 },
    { NOT, 129 },
    { IS, 131 },
    { CMPOP, 133 },
    { LOR, 135 },
    { LAND, 137 },
    { LXOR, 139 },
    { SHIFT, 141 },
    { PLUS, 143 },
    { MINUS, 147 },
    { MULOP, 151 },
    { LNOT, 153 },
    { POW, 155 },
    { OS, 157 },
    { CS, 162 },
    { OC, 165 },
    { CC, 167 },
    { NUMBER, 169 },
    { STRING, 171 },
    { TOKEN_NONE, 173 },
};
#endif /* GRAMMAR_TABLE */

#ifdef TOKEN_NAMES
#undef TOKEN_NAMES
#define token_name(a) token_names[a]
static const char *const token_names[] = {
    0,
    "END",
    "DEF",
    "NAME",
    "OP",
    "CP",
    "COLON",
    "IMPORT",
    "COMMA",
    "ASSIGN",
    "NL",
    "SEMI",
    "RETURN",
    "BREAK",
    "CONTINUE",
    "PASS",
    "GLOBAL",
    "DEL",
    "ASSERT",
    "IF",
    "ELIF",
    "ELSE",
    "WHILE",
    "FOR",
    "IN",
    "RANGE",
    "INDENT",
    "EXDENT",
    "OR",
    "AND",
    "NOT",
    "IS",
    "CMPOP",
    "LOR",
    "LAND",
    "LXOR",
    "SHIFT",
    "PLUS",
    "MINUS",
    "MULOP",
    "LNOT",
    "POW",
    "OS",
    "CS",
    "OC",
    "CC",
    "NUMBER",
    "STRING",
    "start",
    "command",
    "opt-formals",
    "formals",
    "formals-p",
    "formal",
    "opt-named-p",
    "opt-stats",
    "stat",
    "simple-stat",
    "small-stats-p",
    "small-stat",
    "dels-p",
    "del",
    "ret-expr",
    "assign-expr",
    "assign-expr-p",
    "globals",
    "globals-p",
    "global",
    "compound-stat",
    "if-stat",
    "elif-stats",
    "if-expr",
    "while-stat",
    "while-else-stat",
    "for-stat",
    "for-params",
    "suite",
    "expr",
    "expr-or-p",
    "expr-and",
    "expr-and-p",
    "expr-not",
    "expr-cmp",
    "expr-cmp-p",
    "cmpop",
    "expr-lor",
    "expr-lor-p",
    "expr-land",
    "expr-land-p",
    "expr-lxor",
    "expr-lxor-p",
    "expr-shift",
    "expr-shift-p",
    "expr-add",
    "expr-add-p",
    "expr-mul",
    "expr-mul-p",
    "expr-unary",
    "expr-pow",
    "expr-pow-p",
    "expr-array",
    "expr-array-p",
    "array-index",
    "opt-slice",
    "slice",
    "slice-p",
    "opt-expr",
    "expr-prim",
    "strings-p",
    "opt-tuple",
    "opt-tuple-p",
    "opt-actuals",
    "actuals",
    "actual-p",
    "actuals-p",
    "opt-dict-ents",
    "dict-ents-p",
    "dict-ent",
    "dict-ent-p",
};
#endif /* TOKEN_NAMES */

#ifdef PARSE_CODE
#undef PARSE_CODE


static token_t parse_stack[PARSE_STACK_SIZE];

#if PARSE_STACK_SIZE < 256
typedef uint8_t parse_stack_p_t;
#else
#if PARSE_STACK_SIZE < 65536
typedef uint16_t parse_stack_p_t;
#else
typedef uint32_t parse_stack_p_t;
#endif
#endif

#if NON_TERMINAL_SIZE < 256
typedef uint8_t non_terminal_index_t;
#else
#if NON_TERMINAL_SIZE < 65536
typedef uint16_t non_terminal_index_t;
#else
typedef uint32_t non_terminal_index_t;
#endif
#endif

#ifndef PARSE_TABLE_FETCH_TOKEN
#define PARSE_TABLE_FETCH_TOKEN(addr) (*(addr))
#endif
#ifndef PARSE_TABLE_FETCH_INDEX
#define PARSE_TABLE_FETCH_INDEX(addr) (*(addr))
#endif

static const token_t *
match_state(token_t terminal, token_t non_terminal)
{
	token_key_t terminal_key = terminal;
	token_key_t term;
	for (term = 0; term < sizeof(terminal_table) / sizeof(terminal_table[0]); term++)
		if (PARSE_TABLE_FETCH_TOKEN(&terminal_table[term].token) == terminal_key)
			goto got_term;
	return NULL;
got_term:;
	non_terminal_index_t non_term = non_terminal_index(PARSE_TABLE_FETCH_INDEX(&terminal_table[term].index));
	for (;;) {
		uint8_t i = PARSE_TABLE_FETCH_INDEX(&non_terminal_table[non_term]);
		if (i == 0xfe) {
			i = PARSE_TABLE_FETCH_INDEX(&non_terminal_table[non_term+1]);
			non_term = non_terminal_index(i);
		} else if (i == 0xff) {
			break;
		} else {
			const token_t *production = &production_table[production_index(i)];
			if (PARSE_TABLE_FETCH_TOKEN(production) == non_terminal) {
				return production + 1;
			}
			non_term++;
		}
	}
	return NULL;
}

static inline token_t
parse_pop(int *parse_stack_p)
{
    if ((*parse_stack_p) == 0)
	return TOKEN_NONE;
    return parse_stack[--(*parse_stack_p)];
}

static inline bool
parse_push(const token_t *tokens, int *parse_stack_p)
{
    token_t token;
    while ((token = PARSE_TABLE_FETCH_TOKEN(tokens++)) != TOKEN_NONE) {
        if ((*parse_stack_p) >= PARSE_STACK_SIZE)
            return false;
	parse_stack[(*parse_stack_p)++] = token;
    }
    return true;
}

static inline bool
is_terminal(token_t token)
{
    return token < FIRST_NON_TERMINAL;
}

static inline bool
is_action(token_t token)
{
    return token >= FIRST_ACTION;
}

static inline bool
is_non_terminal(token_t token)
{
    return !is_terminal(token) && !is_action(token);
}

typedef enum {
    parse_return_success,
    parse_return_syntax,
    parse_return_end,
    parse_return_oom,
    parse_return_error,
} __attribute__((packed)) parse_return_t;

static parse_return_t
parse(void *lex_context)
{
    token_t token = TOKEN_NONE;
    int parse_stack_p = 0;

    parse_stack[parse_stack_p++] = NON_TERMINAL_start;

    for (;;) {
	token_t top = parse_pop(&parse_stack_p);

	if (is_action(top)) {
	    switch(top) {
    case ACTION_119:
#line 281 "../../../snek-gram.ll"
        
				goto patch_loop;
			; break;
    case ACTION_120:
#line 416 "../../../snek-gram.ll"
         goto unop_first; ; break;
    case ACTION_121:
#line 213 "../../../snek-gram.ll"
        
				goto else_branch;
			; break;
    case ACTION_122:
#line 431 "../../../snek-gram.ll"
         goto binop_first; ; break;
    case ACTION_123:
#line 421 "../../../snek-gram.ll"
         goto unop_second; ; break;
    case ACTION_124:
#line 347 "../../../snek-gram.ll"
        
				goto short_second;
			; break;
    case ACTION_125:
#line 431 "../../../snek-gram.ll"
         goto binop_second; ; break;
    case ACTION_126:
#line 123 "../../../snek-gram.ll"
        {
				goto add_op_lvalue;
			}; break;
    case ACTION_127:
#line 573 "../../../snek-gram.ll"
        {
				value_push_offset(0);
			}; break;
    case ACTION_128:
#line 477 "../../../snek-gram.ll"
        { value_push_bool(true); }; break;
    case ACTION_129:
#line 481 "../../../snek-gram.ll"
        { value_push_bool(false); }; break;
    case ACTION_130:
#line 14 "../../../snek-gram.ll"
        { snek_parse_middle = false; }; break;
    case ACTION_131:
#line 418 "../../../snek-gram.ll"
        {
				value_push_op(snek_op_uminus);
			}; break;
    case ACTION_132:
#line 129 "../../../snek-gram.ll"
        { snek_code_add_op(snek_op_null); }; break;
    case ACTION_133:
#line 36 "../../../snek-gram.ll"
        {
				value_push_id(snek_token_val.id);
	 		}; break;
    case ACTION_134:
#line 102 "../../../snek-gram.ll"
        { snek_code_add_op(snek_op_return); }; break;
    case ACTION_135:
#line 111 "../../../snek-gram.ll"
        { snek_code_add_op(snek_op_assert); }; break;
    case ACTION_136:
#line 17 "../../../snek-gram.ll"
        { snek_print_val = snek_interactive; }; break;
    case ACTION_137:
#line 218 "../../../snek-gram.ll"
        {
				/* push 1 - elif_stats_off */
				value_push_offset(snek_code_current());
			}; break;
    case ACTION_138:
#line 308 "../../../snek-gram.ll"
        {
				value_push_indent(snek_token_val.indent);
			}; break;
    case ACTION_139:
#line 104 "../../../snek-gram.ll"
        { snek_code_add_forward(snek_forward_break); }; break;
    case ACTION_140:
#line 550 "../../../snek-gram.ll"
        {
				snek_code_set_push(snek_code_prev_insn());
			}; break;
    case ACTION_141:
#line 523 "../../../snek-gram.ll"
        {
				snek_code_add_number(snek_token_val.number);
			}; break;
    case ACTION_142:
#line 527 "../../../snek-gram.ll"
        {
				snek_code_add_string(snek_token_val.string);
			}; break;
    case ACTION_143:
#line 544 "../../../snek-gram.ll"
        {
				value_push_offset(0);
				value_push_bool(true);
			}; break;
    case ACTION_144:
#line 106 "../../../snek-gram.ll"
        { snek_code_add_forward(snek_forward_continue); }; break;
    case ACTION_145:
#line 355 "../../../snek-gram.ll"
        {
			unop_first:
				value_push_op(snek_token_val.op);
			}; break;
    case ACTION_146:
#line 31 "../../../snek-gram.ll"
        {
				snek_parse_nformal = 0;
				snek_parse_nnamed = 0;
			}; break;
    case ACTION_147:
#line 360 "../../../snek-gram.ll"
        {
			unop_second:
				snek_code_add_op(value_pop().op);
			}; break;
    case ACTION_148:
#line 374 "../../../snek-gram.ll"
        {
			binop_second:
				snek_code_add_op(value_pop().op);
			}; break;
    case ACTION_149:
#line 82 "../../../snek-gram.ll"
        {
				if (snek_parse_nnamed)
					return parse_return_syntax;
			}; break;
    case ACTION_150:
#line 519 "../../../snek-gram.ll"
        {
				snek_code_add_op_id(snek_op_id, snek_token_val.id);
			}; break;
    case ACTION_151:
#line 95 "../../../snek-gram.ll"
        { snek_code_add_op_offset(snek_op_line, snek_lex_line); }; break;
    case ACTION_152:
#line 119 "../../../snek-gram.ll"
        {
				snek_token_val.op = snek_op_del;
				goto extract_lvalue;
			}; break;
    case ACTION_153:
#line 182 "../../../snek-gram.ll"
        {
				snek_code_add_op_id(snek_op_global, snek_token_val.id);
			}; break;
    case ACTION_154:
#line 459 "../../../snek-gram.ll"
        {
				snek_code_add_op_offset(snek_op_call, value_pop().offset);
			}; break;
    case ACTION_155:
#line 71 "../../../snek-gram.ll"
        {
				snek_parse_formals[snek_parse_nformal++] = snek_token_val.id;
			}; break;
    case ACTION_156:
#line 483 "../../../snek-gram.ll"
        {
				snek_code_set_push(snek_code_prev_insn());
				value_push_bool(true);
			}; break;
    case ACTION_157:
#line 91 "../../../snek-gram.ll"
        { snek_print_val = false; snek_code_add_op_offset(snek_op_line, snek_lex_line); }; break;
    case ACTION_158:
#line 514 "../../../snek-gram.ll"
        {
				snek_offset_t num = value_pop().offset;
				snek_code_add_op_offset(snek_op_dict, num);
			}; break;
    case ACTION_159:
#line 625 "../../../snek-gram.ll"
        {
				snek_code_set_push(snek_code_prev_insn());
				value_push_offset(value_pop().offset + 1);
			}; break;
    case ACTION_160:
#line 326 "../../../snek-gram.ll"
        {
				snek_code_add_op_offset(snek_op_branch_true, 0);
				value_push_offset(snek_compile_prev);
			}; break;
    case ACTION_161:
#line 224 "../../../snek-gram.ll"
        {
				snek_code_add_op_offset(snek_op_branch_false, 0);

				/* push 0 - if_expr_off */
				value_push_offset(snek_compile_prev);
			}; break;
    case ACTION_162:
#line 595 "../../../snek-gram.ll"
        {
				snek_code_set_push(snek_code_prev_insn());
				value_push_offset(value_pop().offset + 256);
			}; break;
    case ACTION_163:
#line 300 "../../../snek-gram.ll"
        {
				snek_id_t id = value_pop().id;
				snek_code_add_in_enum(id, for_depth);
				goto for_push_prevs;
			}; break;
    case ACTION_164:
#line 368 "../../../snek-gram.ll"
        {
			binop_first:
				snek_code_set_push(snek_code_prev_insn());
				value_push_op(snek_token_val.op);
			}; break;
    case ACTION_165:
#line 77 "../../../snek-gram.ll"
        {
				snek_parse_nnamed++;
				snek_code_add_op_id(snek_op_assign_named, snek_parse_formals[snek_parse_nformal-1]);
			}; break;
    case ACTION_166:
#line 331 "../../../snek-gram.ll"
        {
			short_second:
				snek_code_patch_branch(value_pop().offset, snek_code_current());
				snek_code_add_op(snek_op_nop);
			}; break;
    case ACTION_167:
#line 165 "../../../snek-gram.ll"
        {
			add_op_lvalue:;
				snek_op_t op = value_pop().offset;
				snek_id_t id = value_pop().id;
				
				/* add the assignment operator */
				snek_code_add_op_id(op, id);
			}; break;
    case ACTION_168:
#line 533 "../../../snek-gram.ll"
        {
				snek_code_set_push(snek_code_prev_insn());
				snek_code_add_string(snek_token_val.string);
				snek_code_add_op(snek_op_plus);
			}; break;
    case ACTION_169:
#line 243 "../../../snek-gram.ll"
        {
				/* push 2 - loop_end_off */
				snek_code_add_op_offset(snek_op_branch, 0);
				value_push_offset(snek_compile_prev);
				/* push 3 - while_else_stat_off */
				value_push_offset(snek_code_current());
			}; break;
    case ACTION_170:
#line 503 "../../../snek-gram.ll"
        {
				snek_offset_t num = value_pop().offset;
				if (num >= 256)
					return parse_return_syntax;
				snek_code_add_op_offset(snek_op_list, num);
			}; break;
    case ACTION_171:
#line 494 "../../../snek-gram.ll"
        {
				bool tuple = value_pop().bools;

				if (tuple) {
					snek_offset_t num = value_pop().offset;
					snek_code_add_op_offset(snek_op_tuple, num);
				}
			}; break;
    case ACTION_172:
#line 272 "../../../snek-gram.ll"
        {
				snek_code_add_op_offset(snek_op_branch, 0);
				/* push 2 - loop_end_off */
				value_push_offset(snek_compile_prev);
				/* push 3 - while_else_stat_off */
				value_push_offset(snek_code_current());
				for_depth--;
			}; break;
    case ACTION_173:
#line 554 "../../../snek-gram.ll"
        {
				snek_offset_t num = value_pop().offset;
				if (num >= 256)
					return parse_return_syntax;
				value_push_offset(num + 1);
				value_push_bool(true);
			}; break;
    case ACTION_174:
#line 200 "../../../snek-gram.ll"
        {
				snek_code_add_op_offset(snek_op_line, snek_lex_line);
			else_branch:
				snek_code_add_forward(snek_forward_if);
				value_push_offset(snek_code_current());
			}; break;
    case ACTION_175:
#line 207 "../../../snek-gram.ll"
        {
				snek_offset_t elif_stats_off = value_pop().offset;
				snek_offset_t if_expr_off = value_pop().offset;
				snek_code_patch_branch(if_expr_off, elif_stats_off);
			}; break;
    case ACTION_176:
#line 600 "../../../snek-gram.ll"
        {
				snek_offset_t offset = value_pop().offset;
				if (offset >= 256)
					return parse_return_syntax;
				value_push_offset(offset + 1);
				snek_code_set_push(snek_code_prev_insn());
			}; break;
    case ACTION_177:
#line 191 "../../../snek-gram.ll"
        {
				snek_offset_t elif_stats_off = value_pop().offset;
				snek_offset_t if_expr_off = value_pop().offset;
				snek_code_patch_branch(if_expr_off, elif_stats_off);
				snek_code_patch_forward(if_expr_off, snek_compile_size,
							snek_forward_if, snek_code_current());
			}; break;
    case ACTION_178:
#line 312 "../../../snek-gram.ll"
        {
				uint8_t indent = value_pop().indent;
				uint8_t exdent = snek_token_val.indent;

				snek_current_indent = indent;
				if (exdent > snek_current_indent) {
					snek_error("mismatching indentation indent %d exdent %d", indent, exdent);
					return parse_return_syntax;
				}
			}; break;
    case ACTION_179:
#line 18 "../../../snek-gram.ll"
        {
				snek_code_t *code = snek_code_finish();
				SNEK_CODE_HOOK_START
				snek_poly_t p = snek_exec(code);
				SNEK_CODE_HOOK_STOP
				if (snek_abort)
					return parse_return_error;
				if (snek_print_val && !snek_is_null(p)) {
					snek_poly_print(stdout, p, 'r');
					putchar('\n');
				}
			}; break;
    case ACTION_180:
#line 286 "../../../snek-gram.ll"
        {
				snek_offset_t num = value_pop().offset;
				if (num >= 256)
					return parse_return_syntax;
				snek_id_t id = value_pop().id;
				snek_code_add_in_range(id, num, for_depth);
			for_push_prevs:
				/* push 0 - for_off */
				value_push_offset(snek_compile_prev);
				/* push 1 - top_off */
				value_push_offset(snek_compile_prev);
				for_depth++;
			}; break;
    case ACTION_181:
#line 441 "../../../snek-gram.ll"
        {
				bool slice = value_pop().bools;
				if (slice) {
					snek_code_set_push(snek_code_prev_insn());
					uint8_t stride = value_pop().bools * SNEK_OP_SLICE_STRIDE;
					uint8_t end = value_pop().bools * SNEK_OP_SLICE_END;
					uint8_t start = value_pop().bools * SNEK_OP_SLICE_START;
					snek_code_add_slice(start | end | stride);
				} else {
					snek_code_add_op(snek_op_array);
				}
 			}; break;
    case ACTION_182:
#line 579 "../../../snek-gram.ll"
        {
				snek_offset_t prev_offset = snek_code_prev_insn();
				uint8_t *prev = snek_code_at(prev_offset);
				snek_id_t id;

				/* look at the previous instruction to figure out
				 * if it's an id.
				 */
				if (*prev != snek_op_id)
					return parse_return_syntax;
				memcpy(&id, prev + 1, sizeof (snek_id_t));
				snek_code_delete_prev();
				snek_code_add_number(id);
				snek_code_set_push(snek_code_prev_insn());
			}; break;
    case ACTION_183:
#line 40 "../../../snek-gram.ll"
        {
				if (snek_compile[snek_compile_prev] == snek_op_return)
					snek_code_delete_prev();
				else
					snek_code_add_op(snek_op_null);
				snek_code_t	*code = snek_code_finish();
				if (!code)
					break;
				snek_func_t	*func = snek_func_alloc(code);
				if (!func)
					break;
				snek_poly_t	poly = snek_func_to_poly(func);
				snek_id_t	id = value_pop().id;

				snek_stack_push(poly);
				snek_poly_t *ref = snek_id_ref(id, true);
				poly = snek_stack_pop();
				if (ref)
					*ref = poly;
			}; break;
    case ACTION_184:
#line 251 "../../../snek-gram.ll"
        {
			patch_loop:;
				snek_offset_t while_else_stat_off = value_pop().offset;
				snek_offset_t loop_end_off = value_pop().offset;
				snek_offset_t while_off = value_pop().offset;
				snek_offset_t top_off = value_pop().offset;

				snek_code_patch_branch(while_off, while_else_stat_off);
				snek_code_patch_branch(loop_end_off, top_off);
				snek_code_patch_forward(while_off, loop_end_off, snek_forward_continue, top_off);
				snek_code_patch_forward(while_off, loop_end_off, snek_forward_break, snek_code_current());
			}; break;
    case ACTION_185:
#line 134 "../../../snek-gram.ll"
        {
			extract_lvalue:
				snek_print_val = false;
				snek_offset_t prev_offset = snek_code_prev_insn();
				uint8_t *prev = snek_code_at(prev_offset);
				snek_id_t id;

				/* look at the previous instruction to figure out what
				 * it was -- an id or an array. All others are illegal
				 */
				switch (*prev) {
				case snek_op_id:
					memcpy(&id, prev + 1, sizeof (snek_id_t));
					break;
				case snek_op_array:
					if (snek_token_val.op != snek_op_del)
						snek_code_set_push(snek_code_prev_prev_insn());
					id = SNEK_ID_NONE;
					break;
				default:
					return parse_return_syntax;
				}
				value_push_id(id);
				value_push_offset(snek_token_val.op);

				/* eliminate the previous instruction having
				 * extracted the useful information from it
				 */
				snek_code_delete_prev();
			}; break;
#line 2235 "snek-gram.h"

	    default:
		break;
	    }
#ifdef PARSE_ACTION_BOTTOM
	    PARSE_ACTION_BOTTOM;
#endif
	    continue;
	}

	if (token == TOKEN_NONE)
	    token = lex(lex_context);

	if (top == TOKEN_NONE) {
	    if (token != END)
	        return parse_return_syntax;
	    return parse_return_success;
	}

#ifdef PARSE_DEBUG
	{
	    int i;
#ifdef token_name
	    printf("token %s stack %s", token_names[token], token_names[top]);
	    for (i = parse_stack_p-1; i >= 0; i--) {
		if (!is_action(parse_stack[i]))
		    printf(" %s", token_names[parse_stack[i]]);
		else
		    printf(" action %d", parse_stack[i]);
	    }
#else
	    printf("token %d stack %d", token, top);
	    for (i = parse_stack_p-1; i >= 0; i--)
		printf(" %d", parse_stack[i]);
#endif
	    printf("\n");
	}
#endif

	if (is_terminal(top)) {
	    if (top != token) {
                if (token == END)
                    return parse_return_end;
		return parse_return_syntax;
            }
	    token = TOKEN_NONE;
	} else {
	    const token_t *tokens = match_state(token, top);

	    if (!tokens)
		return parse_return_syntax;

	    if (!parse_push(tokens, &parse_stack_p))
                return parse_return_oom;
	}
    }
}

#endif /* PARSE_CODE */
