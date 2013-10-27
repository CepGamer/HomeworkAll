module ui
open System.Windows.Forms
open System.Drawing

type World = Water | Terrain | Mountain

type MForm() as this = 
    class
        inherit Form(Width = 610, Height = 545, MaximizeBox = false, FormBorderStyle = FormBorderStyle.Fixed3D)
        let horBord = 500 / 50
        let verBord = 500 / 50
        let mutable penType = Water
        let mutable map = Array2D.init 50 50 (fun _ _ -> Water)
        let buttonW = new Button(   Text = "Water",
                                    Height = 70,
                                    Width = 70,
                                    Visible = true,
                                    Enabled = true,
                                    Left = 520,
                                    Top = 10)
        
        let buttonT = new Button(   Text = "Terrain",
                                    Height = 70,
                                    Width = 70,
                                    Visible = true,
                                    Enabled = true,
                                    Left = 520,
                                    Top = 10 * 2 + 70)
        
        let buttonM = new Button(   Text = "Mountain",
                                    Height = 70,
                                    Width = 70,
                                    Visible = true,
                                    Enabled = true,
                                    Left = 520,
                                    Top = 10 * 3 + 70 * 2)
        
        let buttonS = new Button(   Text = "Import",
                                    Height = 70,
                                    Width = 70,
                                    Visible = true,
                                    Enabled = true,
                                    Left = 520,
                                    Top = 10 * 4 + 70 * 3)
        
        let easel = new PictureBox( Height = 500,
                                    Width = 500,
                                    Top = 10,
                                    Left = 10,
                                    Visible = true,
                                    Enabled = true)

        let easPaint (e: PaintEventArgs) = 
            e.Graphics.Clear(Color.White)
            for i in 0..49 do
                for j in 0..49 do
                    let br = 
                        match map.[i, j] with
                        | Water -> new SolidBrush(Color.Blue)
                        | Terrain -> new SolidBrush(Color.Green)
                        | Mountain -> new SolidBrush(Color.Brown)
                    e.Graphics.FillRectangle (br, horBord * i, verBord * j, horBord, verBord)

        let easMD (e: MouseEventArgs) = 
            let a = e.Location
            map.[a.X / 10, a.Y / 10] <- penType
            easel.Refresh ()

        let easMM (e: MouseEventArgs) = 
            let a = e.Location
            if e.Button <> MouseButtons.None then 
                if a.X < 500 && a.X >= 0 && a.Y < 500 && a.Y >= 0 then
                    if map.[a.X / 10, a.Y / 10] <> penType then 
                        map.[a.X / 10, a.Y / 10] <- penType
                        easel.Refresh()

        do
            this.Controls.Add buttonW
            this.Controls.Add buttonT
            this.Controls.Add buttonM
            this.Controls.Add buttonS
            this.Controls.Add easel
            buttonW.Click.Add (fun _ -> penType <- Water)
            buttonT.Click.Add (fun _ -> penType <- Terrain)
            buttonM.Click.Add (fun _ -> penType <- Mountain)
            easel.Paint.Add easPaint
            easel.MouseDown.Add easMD
            easel.MouseMove.Add easMM
    end

[<EntryPoint>]
Application.Run(new MForm())
