object dm: Tdm
  OldCreateOrder = False
  Height = 403
  Width = 375
  object FDConnection: TFDConnection
    Params.Strings = (
      'Database=C:\Users\VD\Desktop\a\labOnlineStore\ONLINESTORE.FDB'
      'User_Name=SYSDBA'
      'Password=masterkey'
      'CharacterSet=UTF8'
      'DriverID=FB')
    Connected = True
    LoginPrompt = False
    Left = 40
    Top = 40
  end
  object quCategory: TFDQuery
    Active = True
    AfterScroll = quCategoryAfterScroll
    Connection = FDConnection
    SQL.Strings = (
      'select '
      '    category.id,'
      '    category.name,'
      '    category.image,'
      '    category.sort_index'
      'from category'
      'order by category.sort_index, category.name')
    Left = 40
    Top = 96
    object quCategoryID: TIntegerField
      FieldName = 'ID'
      Origin = 'ID'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Required = True
    end
    object quCategoryNAME: TWideStringField
      FieldName = 'NAME'
      Origin = 'NAME'
      Required = True
      Size = 70
    end
    object quCategoryIMAGE: TBlobField
      FieldName = 'IMAGE'
      Origin = 'IMAGE'
    end
    object quCategorySORT_INDEX: TIntegerField
      FieldName = 'SORT_INDEX'
      Origin = 'SORT_INDEX'
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
      '    product.price,'
      '    product.note,'
      '    product.image'
      'from product'
      'order by product.name')
    Left = 112
    Top = 104
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
    object quProductIMAGE: TBlobField
      FieldName = 'IMAGE'
      Origin = 'IMAGE'
    end
  end
  object quFeedback: TFDQuery
    Active = True
    Connection = FDConnection
    SQL.Strings = (
      'select '
      '    feedback.id,'
      '    feedback.fio,'
      '    feedback.phone,'
      '    feedback.email,'
      '    feedback.note,'
      '    feedback.create_datetime'
      'from feedback'
      'order by feedback.create_datetime')
    Left = 184
    Top = 104
  end
  object spFeedbackIns: TFDStoredProc
    Connection = FDConnection
    StoredProcName = 'FEEDBACK_INS'
    Left = 112
    Top = 224
    ParamData = <
      item
        Position = 1
        Name = 'FIO'
        DataType = ftWideString
        ParamType = ptInput
        Size = 70
      end
      item
        Position = 2
        Name = 'PHONE'
        DataType = ftWideString
        ParamType = ptInput
        Size = 15
      end
      item
        Position = 3
        Name = 'EMAIL'
        DataType = ftWideString
        ParamType = ptInput
        Size = 70
      end
      item
        Position = 4
        Name = 'NOTE'
        DataType = ftWideString
        ParamType = ptInput
        Size = 4000
      end>
  end
end
