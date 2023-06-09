//  Linear kinetics  //

Field<scalar>& val = *this;
scalarField    del = mag( 1. / this->patch().deltaCoeffs() );
scalarField    field  = mag(val);
scalarField    frac( field.size(), 0.0 );
scalarField    refVal( field.size(), 0.0 );
scalarField    refGr( field.size(), 0.0 );

const IOdictionary& IOd = this->db().lookupObject<IOdictionary>("transportProperties");
scalar lR = (new dimensionedScalar(IOd.lookup("lR")))->value();

forAll(field, i)
{
  scalar R    = field[i];
  scalar dR   = 1.0;

  scalar alpha  = del[i] / lR;
  scalar adR    = alpha * dR;
  frac[i]   = adR / ( 1 + adR );
  refVal[i] = R;
  refGr[i]  = -R / lR;
}

this->refValue() = pTraits<scalar>::one * refVal;
this->refGrad()  = pTraits<scalar>::one * refGr;
this->valueFraction() = frac;
