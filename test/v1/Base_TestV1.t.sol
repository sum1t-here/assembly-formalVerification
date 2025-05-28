// SPDX-License-Identifier: MIT
pragma solidity ^0.8.26;

import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";
import {Test, console2} from "forge-std/Test.sol";

abstract contract Base_TestV1 is Test {
    HorseStore public horseStore;

    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function testReadValue() public {
        uint256 initalValue = horseStore.readNumberOfHorses();
        assertEq(initalValue, 0);
    }

    function testWriteValue(uint256 numberOfHorses) public {
        horseStore.updateNumberOfHorses(numberOfHorses);
        assertEq(horseStore.readNumberOfHorses(), numberOfHorses);
    }
}
