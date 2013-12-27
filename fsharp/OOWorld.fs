module OOWorld
open System.Drawing
open FsUnit
open NUnit.Framework

[<AbstractClass>]
type Robot(name: string, start: Point, batteryCharge: int32, turPower: int32) = 
    let mutable pos = start
    let mutable currCharge = batteryCharge
    let mutable psTime = 0
    let mutable isDead = false
    let mutable neighbours: Robot list = []
    override x.ToString() = "No string fo' robots!"
    member x.name = name
    member x.turPower = turPower
    member x.dead() = 
        isDead <- true
    member x.where = pos
    member x.status() = isDead
    member x.addNeighbour (f: Robot) = 
        if System.Math.Abs(f.where.X + f.where.Y - x.where.X - x.where.Y) < 3 then
            neighbours <- f :: neighbours
            if f.turPower <= x.turPower then
                f.dead()
    abstract member move: unit -> string
    abstract member recharge: unit -> string

type Car(name, start, charge, turPower) = 
    inherit Robot(name, start, charge, turPower)
        override x.move() = "We are going to go in 4 directions &, if there is another Robot, fight for our lives!"
        override x.recharge() = "In here we are recharging our battery"

type Omni(name, start, charge, turPower) = 
    inherit Car(name, start, charge, turPower)
        override x.move() = "And here I am going to move in 8 directions!"
        override x.recharge() = "Same thing - we are recharching"


type Boat(name, start, charge, turPower) = 
    inherit Robot(name, start, charge, turPower)
        override x.move() = "Same thing as with car, but ON WATER YOU SICK NO I'M NOT"
        override x.recharge() = "We can recharge only if near dock station on water"

type Fly(name, start, charge, turPower) = 
    inherit Robot(name, start, charge, turPower)
        override x.move() = "Any direction if heli & only 3 if Jet"
        override x.recharge() = "Recharge only while in hangar"

type Heli(name, start, charge, turPower) = 
    inherit Fly(name, start, charge, turPower)
        override x.move() = "Move in 8 direction on any surface"
        override x.recharge() = "At any time in any place!"

let a = new Omni("TOMMY", Point(0, 0), 100, 35)
let b = new Car("6 wheeled", Point(1, 0), 50, 25)
let c = new Boat("Sub", Point(10, 10), 20, 0)
let d = new Heli("Tri", Point(0, 1), 80, 50)
a.addNeighbour b
a.addNeighbour c
a.addNeighbour d

[<Test>]
let ``6 wheeled should be dead``() = 
    b.status() |> should be True

[<Test>]
let ``Submarine should be alive``() = 
    c.status() |> should be True

[<Test>]
let ``Tricopter should be alive``() = 
    d.status() |> should be True
