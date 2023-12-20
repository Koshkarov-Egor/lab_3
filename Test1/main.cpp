#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;
SUITE(KeyTest)
{
     TEST(LargeLetters) {
     modAlphaCipher test(L"ÏÐÈÂÅÒ");
     CHECK(true);
     }
     TEST(LargeAndSmallLetters) {
     modAlphaCipher test(L"ÍÎÂÛÉãîä");
     CHECK(true);
     }
     TEST(EmptyKey) {
     CHECK_THROW(modAlphaCipher test(L""),
    cipher_error);
     }
     TEST(Key_with_a_space) {
     CHECK_THROW(modAlphaCipher test(L"êàê äåëà"),
    cipher_error);
     }

     TEST(Key_with_invalid_characters_number) {
     CHECK_THROW(modAlphaCipher test(L"10äíåé"),
    cipher_error);
     }

    TEST(Key_with_invalid_characters_special_character) {
     CHECK_THROW(modAlphaCipher test(L"Ïðàâäà?"),
    cipher_error);
     }
}
struct KeyAB_fixture {
 modAlphaCipher * pointer;
 KeyAB_fixture()
 {
    pointer = new modAlphaCipher(L"ÀÂ");
 }
 ~KeyAB_fixture()
 {
    delete pointer;
 }
};
SUITE(EncryptTest)
{
     TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
     wstring open_text =
    L"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß";

     wstring result_correct =
    L"ÀÃÂÅÄÆ¨ÈÇÊÉÌËÎÍÐÏÒÑÔÓÖÕØ×ÚÙÜÛÞÝÀß";
     CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
     }
     TEST_FIXTURE(KeyAB_fixture, SmallLetters) {
     wstring open_text =
    L"àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
     wstring result_correct =
    L"ÀÃÂÅÄÆ¨ÈÇÊÉÌËÎÍÐÏÒÑÔÓÖÕØ×ÚÙÜÛÞÝÀß";
     CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
 }
 TEST_FIXTURE(KeyAB_fixture,NumberInText ) {
     wstring open_text = L"äîáðûé1234äå íü";
     CHECK_THROW(pointer->encrypt(open_text),cipher_error);
 }
 TEST_FIXTURE(KeyAB_fixture,TextWithSpecialSymbol)
{
 wstring open_text = L"ïðè/âåò";
 CHECK_THROW(pointer->encrypt(open_text),cipher_error);
 }
 TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
 wstring open_text = L"àëëî àëëî";
 CHECK_THROW(pointer->encrypt(open_text),cipher_error);
 }

}
SUITE(DecryptTest)
{
 TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
 wstring cipher_text =
L"ÀÃÂÅÄÆ¨ÈÇÊÉÌËÎÍÐÏÒÑÔÓÖÕØ×ÚÙÜÛÞÝÀß";
 wstring result_correct =
L"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß";
 CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
 }
 TEST_FIXTURE(KeyAB_fixture, Smallletters) {
 wstring cipher_text =
L"àãâåäæ¸èçêéìëîíðïòñôóöõø÷úùüûþýàÿ";
 wstring result_correct =
L"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß";
 CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
 }

 TEST_FIXTURE(KeyAB_fixture, EmptyText) {
 wstring cipher_text = L"33ïîïóãàÿ";
 CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
 }
 TEST_FIXTURE(KeyAB_fixture,LargeAndSmallLetters )
{
 wstring cipher_text = L"ÇÄðàÂñòóÉÒÅ";

 wstring result_correct = L"ÇÂÐÞÂÏÒÑÉÐÅ";
 CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
 }
 TEST_FIXTURE(KeyAB_fixture,TextWithNumber) {
 wstring cipher_text = L"Íó êàê";
 CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
 }
 TEST_FIXTURE(KeyAB_fixture,TextWithSymbol) {
 wstring cipher_text = L"ïðè/âåò";
 CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
 }
 TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
 wstring cipher_text = L"ïðèâåò";
 CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
 }
}
int main()
{
 return UnitTest::RunAllTests();
}
