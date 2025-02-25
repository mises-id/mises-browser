// Copyright 2018 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


assertEquals(Array.prototype.flat.length, 0);
assertEquals(Array.prototype.flat.name, 'flat');

const input = [1, [2], [[3]]];

assertEquals(input.flat(),          [1, 2, [3]]);
assertEquals(input.flat(1),         [1, 2, [3]]);
assertEquals(input.flat(true),      [1, 2, [3]]);
assertEquals(input.flat(undefined), [1, 2, [3]]);

assertEquals(input.flat(-Infinity), [1, [2], [[3]]]);
assertEquals(input.flat(-1),        [1, [2], [[3]]]);
assertEquals(input.flat(-0),        [1, [2], [[3]]]);
assertEquals(input.flat(0),         [1, [2], [[3]]]);
assertEquals(input.flat(false),     [1, [2], [[3]]]);
assertEquals(input.flat(null),      [1, [2], [[3]]]);
assertEquals(input.flat(''),        [1, [2], [[3]]]);
assertEquals(input.flat('foo'),     [1, [2], [[3]]]);
assertEquals(input.flat(/./),       [1, [2], [[3]]]);
assertEquals(input.flat([]),        [1, [2], [[3]]]);
assertEquals(input.flat({}),        [1, [2], [[3]]]);
assertEquals(
  input.flat(new Proxy({}, {})),    [1, [2], [[3]]]);
assertEquals(input.flat((x) => x),  [1, [2], [[3]]]);
assertEquals(
  input.flat(String),               [1, [2], [[3]]]);

assertEquals(input.flat(2),         [1, 2, 3]);
assertEquals(input.flat(Infinity),  [1, 2, 3]);

assertThrows(() => { input.flat(Symbol()); }, TypeError);
assertThrows(() => { input.flat(Object.create(null)); }, TypeError);
