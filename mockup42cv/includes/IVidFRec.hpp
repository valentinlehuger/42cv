/* Interface pour video_facerec */

#ifndef IVIDFREC_INTERFACE_H
# define  IVIDFREC_INTERFACE_H

class IVidFRec {
public:
  virtual bool		trainModelFromCsv(std::string const pathToCsv) = 0; /* Exception ou retour true/false si erreur, a voir  */
  virtual cv::Mat*	getNextFrameRGB(void) = 0; /* exception ou retour NULL si erreur, a voir */ /* Le widget principal gere l'affichage et le delete du pointeur */
  virtual ~IVidFRec(void) {}
};

#endif /* IVIDFREC_INTERFACE_H */
