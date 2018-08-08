/*
 * Description: 
 *     History: yang@haipo.me, 2017/03/16, create
 */

# ifndef _ME_MARKET_H_
# define _ME_MARKET_H_

# include "me_config.h"

extern uint64_t order_id_start;
extern uint64_t deals_id_start;

/*
交易订单如何防止攻击  核心数据结构
*/
typedef struct order_t {
    uint64_t        id;    /* 标记ID */
    uint32_t        type;  /* 市价单 限价单 */
    uint32_t        side;   /* ask or  bid */
    double          create_time; /* 创建时间 */
    double          update_time; /* 更新时间 */
    uint32_t        user_id;  /* 发起用户id */
    char            *market; /* 市场 */
    char            *source; /* 来源 */
    mpd_t           *price;   /* 价格 */
    mpd_t           *amount;  /* 数量 */
    mpd_t           *taker_fee;  /* 买方费率  */
    mpd_t           *maker_fee; /* 卖方费率 */
    mpd_t           *left;  /* 数量 */
    mpd_t           *freeze; /* 冻结 */
    mpd_t           *deal_stock; /* 成交股票数量 */
    mpd_t           *deal_money; /* 成交金额 */
    mpd_t           *deal_fee;  /* 费用 */
} order_t;

/* 交易市场Desc */
typedef struct market_t {
    char            *name; /* 名字 */
    char            *stock; /* 数字货币 */
    char            *money; /* 数字货币等价物 */

    int             stock_prec;
    int             money_prec;
    int             fee_prec;
    mpd_t           *min_amount; /* 最小交易量 */

    dict_t          *orders; /* 订单 */
    dict_t          *users;

    skiplist_t      *asks; /* 卖方订单 */
    skiplist_t      *bids; /* 买方订单 */
} market_t;

market_t *market_create(struct market *conf);
int market_get_status(market_t *m, size_t *ask_count, mpd_t *ask_amount, size_t *bid_count, mpd_t *bid_amount);

int market_put_limit_order(bool real, json_t **result, market_t *m, uint32_t user_id, uint32_t side, mpd_t *amount, mpd_t *price, mpd_t *taker_fee, mpd_t *maker_fee, const char *source);
int market_put_market_order(bool real, json_t **result, market_t *m, uint32_t user_id, uint32_t side, mpd_t *amount, mpd_t *taker_fee, const char *source);
int market_cancel_order(bool real, json_t **result, market_t *m, order_t *order);

int market_put_order(market_t *m, order_t *order);

json_t *get_order_info(order_t *order);
order_t *market_get_order(market_t *m, uint64_t id);
skiplist_t *market_get_order_list(market_t *m, uint32_t user_id);

sds market_status(sds reply);

# endif

