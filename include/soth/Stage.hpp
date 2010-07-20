#ifndef __SOTH_STAGE__
#define __SOTH_STAGE__

#include "soth/Algebra.h"
#include "soth/BaseY.hpp"
#include "soth/Bound.hpp"

namespace soth
{

  /* --- STAGE -------------------------------------------------------------- */
  /* --- STAGE -------------------------------------------------------------- */
  /* --- STAGE -------------------------------------------------------------- */



  class Stage
  {
  public:
    typedef VectorXi Indirect;

  protected:
    const MatrixXd & J;
    const bound_vector_t & bounds;
    BaseY & Y;

    unsigned int nr,nc; // nr=nbCols(J), nc=nbRows(J).

    MatrixXd W_;
    MatrixXd ML_;
    VectorXd e_;

    //SubMatrixXd M,L;
    //SubVector e;

    //SubMatrixXd L0sq;
    //TriSubMatrixXd L0; // L0 = tri(L0sq)

    //TriMatrixXd Ldamp;

    // fullRankRows = Ir. defRankRows = In.
    //Indirect& Ir,In; // Ir = L0sq.indirect1() -- In =
    //Indirect unactiveRows;

    unsigned int sizeM,sizeL; // sizeL = card(Ir).
    unsigned int sizeA; // sizeA = card(Ir) + card(In).

    /* W = W_( :,[In Ir] ).
     * M = ML_( [In Ir],0:sizeM-1 ).
     * L = ML_( Ir,sizeM:sizeM+sizeL-1  ).
     * Lo = [0;L] = ML_( [In Ir],sizeM:sizeM+sizeL-1  ).
     *
     * W_*ML_ = W*[M [ zeros(In.size(),rank); L ] ]
     */

  public:

    Stage( const MatrixXd & J, const bound_vector_t & bounds, BaseY& Y  );

    /* --- INIT ------------------------------------------------------------- */

    void computeInitialCOD( const unsigned int previousRank,
			    const Indirect & initialIr );
    /*
      ML=J(initIr,:)*Y;
      rank=Ir.size();  Ir=1:rank;
      M=submatrix(ML,1:previousRank); L=submatrix(ML,previousRank+1:end);

      A=columnMajor(L)  // A==L'
      qr(A);
      RotationHouseHolder_list_t Yup( A );
      Y=Y*Yup;

      for i=rank:-1:1
        if( L(i,i)!= 0 ) break;
	nullifyLineDeficient( i );

     */


    //void nullifyLineDeficient( const unsigned int r );
    /*
      Jd = L.row(r);
      foreach i in rank:-1:1
        if( Jd(i)==0 ) continue;
	gr= GR(L(Ir(i),i),Jd(i),i,r );
	L=gr*L;
	W=W*gr';
      Ir >> r;
      In << r;
     */

    /* --- DOWN ------------------------------------------------------------- */

    // Return true if the rank re-increase operated at the current stage.
    //bool downdate( const unsigned int position,
    //RotationGiven_list_t & Ydown );
    /*
      gr = Neutralize row <position> in W <position>
      L=gr'*L
      bool res;
      if( L(In.last(),0) == 0
        // Rank deficience: regularize Hessenberg
	Ydown = regularizeHessenberg
	res=false;
      else
        // No rank dec: quit
	Ir << In.pop();
	res=true;
      Ir >> r; In >> r;
      Unused << r;
      return res;
     */


    // Return true if the rank decrease operated at the current stage.
    //bool propagateDowndate( RotationGiven_list_t & Ydown,
    //bool decreasePreviousRank );
    /*
      M=M*Ydown;
      if(! decreasePreviousRank ) return true;
      L.indices2().push_front( M.indice2().pop_back() );

      foreach i in In
        if( L(i,0) == 0 continue;
	Ir << i; In >> i;
        return true;

      Ydown += regularizeHessenberg
      return false
     */

    //void regularizeHessenberg( RotationGiven_list_t & Ydown,
    //unsigned int i0 = 0 );
    /*
      for i=i0:rank-1
        gr = GR( L(Ir(i),i),L(Ir(i),i+1),i,i+1 );
	L = L*GR;
	Ydown.push_back( gr );
     */

    /* --- UPD -------------------------------------------------------------- */

    /* TODO
      if stage(sup).update( Jup,Yup )
        while stage(sup++).propagateUpdate( Yup,false
      else ..

     */

    // Return true if the rank re-decrease operated at the current stage.
    //bool update( const VectorXd & Jup,
    //RotationGiven_list_t & Yup );
    /*
      Inew = Unused.pop();
      Row JupY = row(Inew);
      JupU = Jup*Y;
      double norm2=0; double rankJ=0;
      for i=n:-1:1
        norm2+=JupY(i)^2;
	if norm2!=0 rankJ=i; break;

      Ir << Inew
      W(Inew,Inew)=1;
      if rankJ>sizeM+rank
        // Rank increase
        for i=rankJ:-1:sizeM+rank+1
	  Gr gr; gr.init( JupY,i,i-1,0 ); prod(JupY,gr);
	  Yup.push_back( gr );
	return false;
      else
        // No rank increase;
	nullifyLineDeficient(Inew);
	return true;
     */


    // Return true if the rank decrease operated at the current stage.
    //bool propagateUpdate( RotationGiven_list_t & Yup,
    //bool decreasePreviousRank );
    /*
      ML=ML*Yup;
      increaseSizeM();
      if( decreasePreviousRank ) return true
      for i=1:rank
        if L(i,i) == 0
	  // Rank re-decrease
	  nullifyLineDeficient( i );
	  regularizeHessenberg( Yup,i+1 );
	  return true;
      return false;
     */


    /* --- SOLVE ------------------------------------------------------------ */

    //void solve( const VectorXd & e, VectorXd res );
    //void solveTranspose( const VectorXd & e, VectorXd res );

    //void damp( const double & damping );

  public:
    /* --- ACCESSORS --- */

    // SubMatrixXd M();
    // SubMatrixXd L();
    // SubMatrixXd Lo();

    // const_SubMatrixXd M() const ;
    // const_SubMatrixXd L() const ;
    // const_SubMatrixXd Lo() const ;

    // SubRowXd row( const unsigned int r );
    // SubRowXd rown( const unsigned int r ); // row rank def
    // SubRowXd rowf( const unsigned int r ); // row rank full

    /* --- MODIFIORS --- */
    // void increaseSizeM();
    // void decreaseSizeM();

  };




}; // namespace soth


#endif // #ifndef __SOTH_STAGE__