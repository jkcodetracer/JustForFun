/*
 * @FileName: rcu.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年02月26日星期日09:04:33
 * 
 */ 
#define rcu_read_lock()		preempt_disabel()
#define rcu_read_unlock()	preempt_enable()
#define rcu_read_lock_bh()	local_bh_disable()
#define rcu_read_unlock_bh()local_bh_enable()



