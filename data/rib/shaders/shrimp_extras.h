/* Microfacet distribution functions */

////////////////////////////////////////////////////////////////////////////////
/* Beckmann distribution */
float beckmann(
				float cosalpha, roughness;
		)
{
	float tanalpha_over_m = max( 0, sqrt( 1 - SQR(cosalpha)) / cosalpha)
		/ roughness;
	return exp(-SQR(tanalpha_over_m)) / (SQR(roughness)*pow(cosalpha,4));
}

////////////////////////////////////////////////////////////////////////////////
/* Ward distribution */
float ward(
			float cosalpha, roughness;
		)
{
	float tanalpha = max( 0, sqrt( 1 - SQR(cosalpha)) / cosalpha );
	float m2 = SQR(roughness);
	float out = 1 / (m2 * PI * pow( cosalpha, 3 ));
	out *= exp( -(SQR(tanalpha)/m2));
	return out;	
}

////////////////////////////////////////////////////////////////////////////////
/* Trowbridge-Reitz distribution */
/* Note: this distribution needs a normalization factor */

float
trowbridge_reitz(
					float cosalpha, roughness;
					)
{
	float m2 = SQR(roughness);
	float cosalpha2 = SQR(cosalpha);
	float d2 = m2 / (cosalpha2 * (m2-1)+1);
	return SQR(d2);
}

////////////////////////////////////////////////////////////////////////////////
/* Heidrich-Seidel anisotropic distribution, some literature refers to
 * coupling this with a isotropic specular term */
float
heidrich_seidel(
					normal Nf;
					vector Vf, Ln;
					vector xdir; // normalized anisotropy direction
					float roughness;
					)
{
	vector dir = normalize( Nf ^ xdir );
	float beta = Ln.dir;
	float theta = Vf.dir;
	float sinbeta = sqrt( max( 0, 1 - SQR(beta)));
	float sintheta = sqrt( max( 0, 1 - SQR(theta)));
	return pow( sinbeta * sintheta - (beta * theta), 1/roughness);
}

////////////////////////////////////////////////////////////////////////////////
/* Geometric attenuation */

/* Torrance-Sparrow */
float
cook_torrance(
					float costheta, cosalpha, cospsi, cospsi2;
					)
{	
	float shadowing = (cosalpha * costheta) / cospsi2;
	float masking = (cosalpha * cospsi) / cospsi2;

	return min( 1, 2 * min( shadowing, masking) );
}

////////////////////////////////////////////////////////////////////////////////
/* Smith geometric selfshadowing/masking */
/* Product of 2 attenuation terms, between incident vector and microstructure
 * normal, and viewer and microstructure normal. */

float smith(
				float cospsi, costheta, roughness;
				)
{
	float g1 = cospsi / (roughness + (1 - roughness) * cospsi);
	float g2 = costheta / (roughness + (1 - roughness) * costheta);
	return g1 * g2;
}

////////////////////////////////////////////////////////////////////////////////
/* He-Torrance geometric selfshadowing/masking */

float he_torrance(
					float costheta, cosalpha, roughness;
					)
{
	float cosalpha2 = SQR(cosalpha);
	float costheta2 = SQR(costheta);
	float m2 = SQR(roughness);

	float hnl = cosalpha2 / (2 * m2 * (1 - cosalpha2) );
	float hnv = costheta2 / (2 * m2 * (1 - costheta2) );

	float gnl = sqrt( PI * hnl * (2 - mm_erfc( sqrt( hnl ))));
	float gnv = sqrt( PI * hnv * (2 - mm_erfc( sqrt( hnv ))));

	return (gnl / (gnl +1) ) * (gnv / (gnv + 1) );
}

