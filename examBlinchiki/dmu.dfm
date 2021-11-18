object dm: Tdm
  OldCreateOrder = False
  Height = 514
  Width = 711
  object FDConnection: TFDConnection
    Params.Strings = (
      'Database=C:\Users\VD\Desktop\a\examBlinchiki\BLINCHIKI.FDB'
      'Password=masterkey'
      'User_Name=SYSDBA'
      'CharacterSet=UTF8'
      'DriverID=FB')
    Connected = True
    LoginPrompt = False
    Left = 56
    Top = 40
  end
  object quCategory: TFDQuery
    Active = True
    AfterScroll = quCategoryAfterScroll
    Connection = FDConnection
    SQL.Strings = (
      'select '
      '    category.name,'
      '    category.sort_index,'
      '    category.id'
      'from category'
      'order by category.sort_index')
    Left = 56
    Top = 144
    object quCategoryNAME: TWideStringField
      FieldName = 'NAME'
      Origin = 'NAME'
      Required = True
      Size = 70
    end
    object quCategorySORT_INDEX: TIntegerField
      FieldName = 'SORT_INDEX'
      Origin = 'SORT_INDEX'
    end
    object quCategoryID: TIntegerField
      FieldName = 'ID'
      Origin = 'ID'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Required = True
    end
  end
  object quProduct: TFDQuery
    Active = True
    Filtered = True
    Connection = FDConnection
    SQL.Strings = (
      'select '
      '    product.id,'
      '    product.category_id,'
      '    product.name,'
      '    product.image,'
      '    product.gram,'
      '    product.kcal,'
      '    product.price,'
      '    product.note,'
      '    product.sticker'
      'from product'
      'order by product.name')
    Left = 136
    Top = 144
    object quProductID: TIntegerField
      FieldName = 'ID'
      Origin = 'ID'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Required = True
    end
    object quProductCATEGORY_ID: TIntegerField
      FieldName = 'CATEGORY_ID'
      Origin = 'CATEGORY_ID'
      Required = True
    end
    object quProductNAME: TWideStringField
      FieldName = 'NAME'
      Origin = 'NAME'
      Required = True
      Size = 70
    end
    object quProductIMAGE: TBlobField
      FieldName = 'IMAGE'
      Origin = 'IMAGE'
    end
    object quProductGRAM: TIntegerField
      FieldName = 'GRAM'
      Origin = 'GRAM'
    end
    object quProductKCAL: TIntegerField
      FieldName = 'KCAL'
      Origin = 'KCAL'
    end
    object quProductPRICE: TFloatField
      FieldName = 'PRICE'
      Origin = 'PRICE'
      Required = True
    end
    object quProductNOTE: TWideStringField
      FieldName = 'NOTE'
      Origin = 'NOTE'
      Size = 4000
    end
    object quProductSTICKER: TIntegerField
      FieldName = 'STICKER'
      Origin = 'STICKER'
    end
  end
  object FDQuery1: TFDQuery
    Active = True
    Connection = FDConnection
    SQL.Strings = (
      'select * from viproduct_rnd')
    Left = 208
    Top = 144
  end
  object spFeedbackIns: TFDStoredProc
    Connection = FDConnection
    StoredProcName = 'CALLS_INS'
    Left = 336
    Top = 240
    ParamData = <
      item
        Position = 1
        Name = 'FIO'
        DataType = ftSingle
        ParamType = ptInput
      end
      item
        Position = 2
        Name = 'E-MAIL'
        DataType = ftSingle
        ParamType = ptInput
      end
      item
        Position = 3
        Name = 'DESKRIP'
        DataType = ftSingle
        ParamType = ptInput
      end>
  end
end
