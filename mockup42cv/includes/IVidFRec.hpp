// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IVidFRec.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 14:59:53 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 14:59:55 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
/* Interface pour video_facerec */

#ifndef IVIDFREC_INTERFACE_H
# define  IVIDFREC_INTERFACE_H
# include <string>
# include <opencv2/core/core.hpp>

class IVidFRec {
public:
	virtual bool		trainModelFromCsv(std::string const pathToCsv) = 0; /* Exception ou retour true/false si erreur, a voir  */
	virtual cv::Mat*	getNextFrameRGB(void) = 0; /* exception ou retour NULL si erreur, a voir */ /* Le widget principal gere l'affichage et le delete du pointeur */
	virtual bool		releaseVideo(void) = 0;
	virtual ~IVidFRec(void) {}
};

#endif /* IVIDFREC_INTERFACE_H */
