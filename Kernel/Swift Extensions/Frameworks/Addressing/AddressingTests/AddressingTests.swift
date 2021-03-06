//
//  AddressingTests.swift
//  AddressingTests
//
//  Created by Adam Kopeć on 11/5/17.
//  Copyright © 2017 Adam Kopeć. All rights reserved.
//

import XCTest
@testable import Addressing

class AddressingTests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        let addr: UInt = 0x40065
        let address = Address(addr)
        XCTAssert(address.physical == 0x40065)
        XCTAssert(address.virtual  == 0xffffff8000ff23AA)
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }
    
    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }
    
}

@_silgen_name("io_map")
public func io_map(_ phys_addr: UInt64, _ size: UInt, _ flags: UInt32) -> UInt64 {
    return 0xffffff8000ff2345
}

@_silgen_name("kvtophys")
public func kvtophys(_ addr: UInt64) -> UInt64 {
    return 0x40000
}
