#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(comparison_trump){
    const Card ace_hearts(ACE, HEARTS);
    const Card two_spades(TWO, SPADES);
    //bool hello = Card_less(ace_hearts, two_spades, ACE);
    ASSERT_EQUAL(Card_less(ace_hearts, two_spades, HEARTS), false)

}

TEST(gettrumpsuit){
    ASSERT_EQUAL(Card(JACK, SPADES).get_suit(CLUBS), CLUBS);
    ASSERT_EQUAL(Card(JACK, CLUBS).get_suit(SPADES), SPADES);
    ASSERT_EQUAL(Card(JACK, DIAMONDS).get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(Card(JACK, HEARTS).get_suit(DIAMONDS), DIAMONDS);
}

TEST(faceorace){
    ASSERT_TRUE(Card(JACK, CLUBS).is_face_or_ace());
    ASSERT_TRUE(Card(QUEEN, HEARTS).is_face_or_ace());
    ASSERT_TRUE(Card(KING, DIAMONDS).is_face_or_ace());
    ASSERT_TRUE(Card(ACE, SPADES).is_face_or_ace());
}

TEST(bowerandtrump){
    ASSERT_TRUE(Card(JACK, CLUBS).is_left_bower(SPADES));
    ASSERT_TRUE(Card(JACK, HEARTS).is_left_bower(DIAMONDS));
    ASSERT_TRUE(Card(JACK, CLUBS).is_right_bower(CLUBS));
    ASSERT_TRUE(Card(JACK, DIAMONDS).is_left_bower(HEARTS));
    ASSERT_TRUE(Card(JACK, CLUBS).is_trump(CLUBS));
    ASSERT_TRUE(Card(JACK, CLUBS).is_trump(SPADES));
}

TEST(suit_next){
    ASSERT_EQUAL(Suit_next(Card(TWO, HEARTS).get_suit()), DIAMONDS);
}

TEST(cintest){
    istringstream is("Ten of Hearts\nKing of Clubs Nine of Spades");
    Card a, b, c;
    is >> a >> b >> c;
    ASSERT_EQUAL(a, Card(TEN, HEARTS));
    ASSERT_EQUAL(b, Card(KING, CLUBS));
    ASSERT_EQUAL(c, Card(NINE, SPADES));
}

TEST(couttest){
    ostringstream os;
    os << Card(TWO, SPADES) << " " << Card(TEN, HEARTS);
    ASSERT_EQUAL(os.str(), string("Two of Spades Ten of Hearts"));
}

TEST(comparisontests){
    ASSERT_TRUE(Card(NINE, SPADES) < Card(NINE, HEARTS));
    ASSERT_TRUE(Card(NINE, HEARTS) < Card(NINE, CLUBS));
    ASSERT_TRUE(Card(NINE, CLUBS) < Card(NINE, DIAMONDS));
    ASSERT_TRUE(Card(NINE, DIAMONDS) < Card(TEN, SPADES));  // rank beats suit
    ASSERT_FALSE(Card(TEN, SPADES) < Card(NINE, DIAMONDS));
    ASSERT_FALSE(Card(ACE, HEARTS) < Card(ACE, HEARTS));
    ASSERT_TRUE(Card(ACE, HEARTS) <= Card(ACE, HEARTS));
  
}

TEST(cardless){
    ASSERT_TRUE(Card_less(Card(JACK, HEARTS), Card(JACK, DIAMONDS), DIAMONDS));
    ASSERT_FALSE(Card_less(Card(JACK, DIAMONDS), Card(JACK, HEARTS), DIAMONDS));
    ASSERT_TRUE(Card_less(Card(ACE, DIAMONDS), Card(JACK, HEARTS), DIAMONDS));
    ASSERT_TRUE(Card_less(Card(ACE, SPADES), Card(NINE, DIAMONDS), DIAMONDS));
    ASSERT_FALSE(Card_less(Card(JACK, DIAMONDS), Card(JACK, DIAMONDS), DIAMONDS));
}





// Add more test cases here

TEST_MAIN()
