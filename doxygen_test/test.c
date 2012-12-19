/**
 * @file  test.c
 * @author  wzj
 * @brief  网整洁
 * @history  
 * @date  2012年07月30日星期一23:09:38
 * @note you fucking gays must know one thing. programer is 
 * 		an attitude.
 */

/**
 * A class for test the doxygen
 *
 */
struct test{
public:
	/**
	 * An enum,
	 * More detailed enum descriop...
	 */	
	enum TEnum{
		TVal1,	/**< enum value TVal1.*/
		TVal2,	/**< enum value TVal2.*/
		TVal3	/**< enum value TVal3.*/
	}*enumPtr,	/**< enum pointer, Details.*/
	enumVar;	/**< enum variable. Details.*/
	/**
	 * A constructor.
	 * A more elaborate description of destructor
	 */
	 Test();
	/**
	 * A destructor.
	 * A more elavorate description of the destructor
	 */
	 ~Test();
	/**
	 * a normall member taking two arguments
	 * @param a an integer argument.
	 * @param s a constant character pointer
	 * @see Test()
	 * @see ~Test()
	 * @see testMeToo()
	 * @return The test result
	 */
	 int testMe(int a, const char *s);

	/**
	 * a normal member taking two arguments and returning an interger
	 * @see testMe()
	 * @param c1 the first argument.
	 * @param c2 the second argument.
	 */
	 virtual void testMeToo(char c1, char c2) = 0;

	/**
	 * a public variable.
	 * Details.
	 */
	 int publicVar;
	/**
	 * a function varibale.
	 * Details
	 */
	 int (*handler)(int a, int b);
};

