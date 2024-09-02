/*
 *  Copyright 2016 Henry Lee
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*
 * Card id, ranged from 0 to 51.
 *
 * The two least significant bits represent the 4 suits, ranged from 0-3.
 *
 * The rest of it represent the 13 ranks, ranged from 0-12.
 * More specifically:
 * deuce = 0, trey = 1, four = 2, five = 3, six = 4, seven = 5, eight = 6,
 * nine = 7, ten = 8, jack = 9, queen = 10, king = 11, ace = 12.
 *
 * 13 * 4 gives all 52 ids.
 *
 * WARNING: The code doesn't provide any sanity checks. Wrap it in your own
 * function if you need. Otherwise make sure the inputs are within the range 
 * [0, 51].
 */
int evaluate_7cards(int a, int b, int c, int d, int e, int f, int g);
int evaluate_6cards(int a, int b, int c, int d, int e, int f);
int evaluate_5cards(int a, int b, int c, int d, int e);

