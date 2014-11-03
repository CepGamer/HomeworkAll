module Test
open main

type TestLuminary(tmp: LuminaryType) = 
    interface ILuminary with
        member this.isShining() = tmp = LuminaryType.Shining

type TestDaylight (tmp: DaylightType) = 
    interface IDayLight with
        member this.Current = tmp

type TestWind (tmp: WindType) = 
    interface IWind with
        member this.Current = tmp

type TestWeather(lum, dlt, win) = 
    interface IWeatherFactory with
        member this.createDaylight() = new TestDaylight(dlt) :> IDayLight
        member this.createLuminary() = new TestLuminary(lum) :> ILuminary
        member this.createWind() = new TestWind(win) :> IWind
