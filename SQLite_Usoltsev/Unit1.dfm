object Form2: TForm2
  Left = 0
  Top = 0
  ActiveControl = VirtualStringTree1
  Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093' Database'
  ClientHeight = 235
  ClientWidth = 396
  Color = clAppWorkSpace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 9
    Top = 159
    Width = 79
    Height = 21
    Caption = #1048#1089#1090#1086#1095#1085#1080#1082':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 194
    Width = 84
    Height = 21
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 217
    Height = 135
    Header.AutoSizeIndex = 0
    Header.MainColumn = 1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coAllowFocus, coEditable, coStyleColor]
        Position = 0
        Text = 'Id'
      end
      item
        Position = 1
        Text = 'origin'
        Width = 150
      end
      item
        Position = 2
        Text = 'name'
        Width = 62
      end>
  end
  object Button1: TButton
    Left = 247
    Top = 8
    Width = 138
    Height = 41
    Caption = #1047#1072#1087#1086#1083#1085#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 247
    Top = 55
    Width = 138
    Height = 41
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 247
    Top = 102
    Width = 138
    Height = 41
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 3
    OnClick = Button3Click
  end
  object Edit1: TEdit
    Left = 110
    Top = 156
    Width = 275
    Height = 29
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 4
  end
  object Edit2: TEdit
    Left = 110
    Top = 191
    Width = 275
    Height = 29
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 5
  end
end
