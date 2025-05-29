// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.26;

interface IHorseStore {
    function updateNumberOfHorses(uint256 newNumberOfHorses) external;
    function readNumberOfHorses() external view returns (uint256);
}