
std::vector<const xAOD::TruthParticle*> q_from_V;
if(m_isMC){
    for (const xAOD::TruthParticle*particle : *particles){
        if (particle->parent(0))
            if(particle->status()==23 && abs(particle->pdgId())<5 && fabs((particle->parent(0))->pdgId())==23 || fabs((particle->parent(0))->pdgId())==24)) {
                q_from_V.push_back(particle);
            }
    }
}
xAOD::Jet*jet1_from_V=0;
xAOD::Jet*jet2_from_V=0;
float dR1=999.;
float dR2=999.;
for(xAOD::Jet*jet : *jets){
    if(q_from_V.size()<2) Props::isVqqTruth.set(jet,0);
    else if(q_from_V.at(0)->p4().DeltaR(jet->p4())<0.4 && q_from_V.at(0)->p4().DeltaR(jet->p4())<dR1){
        dR1= q_from_V.at(0)->p4().DeltaR(jet->p4());
        if(jet1_from_V) Props::isVqqTruth.set(jet1_from_V,0);
        jet1_from_V=jet;
    }
    else if(q_from_V.at(1)->p4().DeltaR(jet->p4())<0.4 && q_from_V.at(1)->p4().DeltaR(jet->p4())<dR2){
        dR2= q_from_V.at(1)->p4().DeltaR(jet->p4());
        if(jet2_from_V) Props::isVqqTruth.set(jet2_from_V,0);
        jet2_from_V=jet;
    }
    else Props::isVqqTruth.set(jet,0);
}

if(jet1_from_V) Props::isVqqTruth.set(jet1_from_V,1);
if(jet2_from_V) Props::isVqqTruth.set(jet2_from_V,1); 

