/* 
 * File:   UnitTest.h
 * Author: dthedens
 *
 * Created on June 30, 2014, 10:46 AM
 */

#ifndef UNITTEST_H
#define	UNITTEST_H

#ifdef	__cplusplus
extern "C" {
#endif

// define this 1 to enable unit tests otherwise 0
#define UNIT_TESTS 0

typedef enum _UNIT_TEST_RESULT { UnitTestFail = 0, UnitTestSuccess } UnitTestResult_t;


#ifdef	__cplusplus
}
#endif

#endif	/* UNITTEST_H */

